#pragma once

#include <cstring>
#include "callbacklist.h"
#include "core/core_utility.h"

namespace eventpp {

namespace internal_ {

template <
	typename EventType_,
	typename Prototype_,
	typename Policies_,
	typename MixinRoot_
>
class EventDispatcherBase;

template <
	typename EventType_,
	typename Policies_,
	typename MixinRoot_,
	typename ReturnType, typename ...Args
>
class EventDispatcherBase <
	EventType_,
	ReturnType (Args...),
	Policies_,
	MixinRoot_
>
{
protected:
	using ThisType = EventDispatcherBase<
		EventType_,
		ReturnType (Args...),
		Policies_,
		MixinRoot_
	>;
	using MixinRoot = typename std::conditional<
		std::is_same<MixinRoot_, void>::value,
		ThisType,
		MixinRoot_
	>::type;
	using Policies = Policies_;

	using Threading = typename SelectThreading<Policies_, HasTypeThreading<Policies_>::value>::Type;

	using ArgumentPassingMode = typename SelectArgumentPassingMode<
		Policies_,
		HasTypeArgumentPassingMode<Policies_>::value,
		ArgumentPassingAutoDetect
	>::Type;

	using Callback_ = typename SelectCallback<
		Policies_,
		HasTypeCallback<Policies_>::value,
		std::function<ReturnType (Args...)>
	>::Type;
	using CallbackList_ = CallbackList<ReturnType (Args...), Policies_>;

	using Prototype = ReturnType (Args...);

	using Map = typename SelectMap<
		EventType_,
		CallbackList_,
		Policies_,
		HasTemplateMap<Policies_>::value
	>::Type;

	using Mixins = typename internal_::SelectMixins<
		Policies_,
		internal_::HasTypeMixins<Policies_>::value
	>::Type;

public:
	using Handle = typename CallbackList_::Handle;
	using Callback = Callback_;
	using Event = EventType_;
	using Mutex = typename Threading::Mutex;

public:
	EventDispatcherBase()
		:
			eventCallbackListMap(),
			listenerMutex()
	{
	}

	EventDispatcherBase(const EventDispatcherBase & other)
		:
			eventCallbackListMap(other.eventCallbackListMap),
			listenerMutex()
	{
	}

	EventDispatcherBase(EventDispatcherBase && other) noexcept
		:
			eventCallbackListMap(std::move(other.eventCallbackListMap)),
			listenerMutex()
	{
	}

	EventDispatcherBase & operator = (const EventDispatcherBase & other)
	{
		eventCallbackListMap = other.eventCallbackListMap;
		return *this;
	}

	EventDispatcherBase & operator = (EventDispatcherBase && other) noexcept
	{
		eventCallbackListMap = std::move(other.eventCallbackListMap);
		return *this;
	}

	void swap(EventDispatcherBase & other) noexcept {
		using std::swap;
		
		swap(eventCallbackListMap, other.eventCallbackListMap);
	}

	template<typename E>
	Handle appendListener(const Callback &callback) {
		std::lock_guard<Mutex> lockGuard(listenerMutex);
		return eventCallbackListMap[typeid(E)].append(callback);
	}

	Handle appendListener(const Event & event, const Callback & callback) {
		std::lock_guard<Mutex> lockGuard(listenerMutex);
		return eventCallbackListMap[event].append(callback);
	}

	template<typename Func>
	Handle subscribe(Func callback) {
		using EventType = typename type_traits::first_func_argument<decltype(&Func::operator())>::type;
		//static_assert(std::is_same_v<ArgType, E>, "Incorrect function argument");

		return appendListener(typeid(EventType), callback);
	}

	template<typename EventType>
	Handle subscribe(void (*callback)(EventType)) {
		//using ArgType = typename first_func_argument<callback>::type;
		//static_assert(std::is_same_v<ArgType, E>, "Incorrect function argument");

		return appendListener(typeid(EventType), callback);
	}

	Handle prependListener(const Event & event, const Callback & callback) {
		std::lock_guard<Mutex> lockGuard(listenerMutex);
		return eventCallbackListMap[event].prepend(callback);
	}

	Handle insertListener(const Event & event, const Callback & callback, const Handle & before) {
		std::lock_guard<Mutex> lockGuard(listenerMutex);
		return eventCallbackListMap[event].insert(callback, before);
	}

	template<typename EventType>
	bool contains(void (*callback)(EventType)) {
		return containsListener(typeid(EventType), callback);
	}

	template<typename Func>
	bool contains(Func callback) {
		using EventType = typename type_traits::first_func_argument<decltype(&Func::operator())>::type;
		return containsListener(typeid(EventType), callback);
	}

	bool containsListener(const Event &event, const Callback &pcb) {
		CallbackList_ *callableList = doFindCallableList(event);
		bool result = false;
		if (callableList) {
			callableList->forEach([&result, callableList, &pcb] (const Handle &handle, const Callback &callback) {
				const auto &ca = pcb.target_type();
				const auto &cb = callback.target_type();
				if (ca == cb) {
					result |= true;
				}
			});
		}

		return result;
	}

	template<typename E>
	bool removeListener(const Callback &pcb) {
		return removeListener(typeid(E), pcb);
	}

	template<typename Func>
	bool unsubscribe(Func pcb) {
		using ArgType = typename type_traits::first_func_argument<Func>::type;
		return removeListener(typeid(ArgType), pcb);
	}

	template<typename EventType>
	bool unsubscribe(void (*callback)(EventType)) {
		return removeListener(typeid(EventType), callback);
	}

	struct FunctionAccess {
		void *vtable;
		void *storage;
	};

	bool removeListener(const Event &event, const Callback & pcb) {
		CallbackList_ *callableList = doFindCallableList(event);
		bool result = false;
		if (callableList) {
			callableList->forEach([&result, callableList, &pcb] (const Handle &handle, const Callback &callback) {
				const auto &ca = pcb.target_type();
				const auto &cb = callback.target_type();
				if (ca != cb) {
					return;
				}

				auto pfa = pcb.template target<ReturnType(*)(Args...)>();
				auto pfb = callback.template target<ReturnType(*)(Args...)>();
				if (pfa && pfb) {
					if (*pfa == *pfb) {
						callableList->remove(handle);
						result = true;
						return;
					}
				}
				// hack, but we just need to check address from raw functions
				// so this should work (msvc works fine), hope it will work on gcc/clang also
				auto tfa = reinterpret_cast<const FunctionAccess *>(&pcb);
				auto tfb = reinterpret_cast<const FunctionAccess *>(&callback);

				if (tfa->storage == tfb->storage) {
					callableList->remove(handle);
					result = true;
					return;
				}
			});
		}

		return result;
	}

	void  removeListeners() {
		eventCallbackListMap.clear();
	}

	bool removeListener(const Event & event, const Handle handle)
	{
		CallbackList_ * callableList = doFindCallableList(event);
		if(callableList) {
			return callableList->remove(handle);
		}

		return false;
	}

	bool hasAnyListener(const Event & event) const
	{
		const CallbackList_ * callableList = doFindCallableList(event);
		if(callableList) {
			return !callableList->empty();
		}

		return false;
	}

	bool ownsHandle(const Event & event, const Handle & handle) const
	{
		const CallbackList_ * callableList = doFindCallableList(event);
		if(callableList) {
			return callableList->ownsHandle(handle);
		}

		return false;
	}

	template <typename Func>
	void forEach(const Event & event, Func && func) const
	{
		const CallbackList_ * callableList = doFindCallableList(event);
		if(callableList) {
			callableList->forEach(std::forward<Func>(func));
		}
	}

	template <typename Func>
	bool forEachIf(const Event & event, Func && func) const
	{
		const CallbackList_ * callableList = doFindCallableList(event);
		if (callableList) {
			return callableList->forEachIf(std::forward<Func>(func));
		}

		return true;
	}

	void dispatch(Args ...args) const
	{
		static_assert(ArgumentPassingMode::canIncludeEventType, "Dispatching arguments count doesn't match required (Event type should be included).");

		using GetEvent = typename SelectGetEvent<Policies_, EventType_, HasFunctionGetEvent<Policies_, Args...>::value>::Type;

		// can't std::forward<Args>(args) in GetEvent::getEvent because the pass by value arguments will be moved to getEvent
		// then the other std::forward<Args>(args) to directDispatch will get empty values.
		directDispatch(
			GetEvent::getEvent(args...),
			std::forward<Args>(args)...
		);
	}

	template <typename T>
	void dispatch(T && first, Args ...args) const
	{
		static_assert(ArgumentPassingMode::canExcludeEventType, "Dispatching arguments count doesn't match required (Event type should NOT be included).");

		using GetEvent = typename SelectGetEvent<Policies_, EventType_, HasFunctionGetEvent<Policies_, T &&, Args...>::value>::Type;

		directDispatch(
			GetEvent::getEvent(std::forward<T>(first), args...),
			std::forward<Args>(args)...
		);
	}

	// Bypass any getEvent policy. The first argument is the event type.
	// Most used for internal purpose.
	void directDispatch(const Event & e, Args ...args) const
	{
		if(! internal_::ForEachMixins<MixinRoot, Mixins, DoMixinBeforeDispatch>::forEach(
			this, typename std::add_lvalue_reference<Args>::type(args)...)) {
			return;
		}

		const CallbackList_ * callableList = doFindCallableList(e);
		if(callableList) {
			(*callableList)(std::forward<Args>(args)...);
		}
	}

protected:
	const CallbackList_ * doFindCallableList(const Event & e) const
	{
		return doFindCallableListHelper(this, e);
	}

	CallbackList_ * doFindCallableList(const Event & e)
	{
		return doFindCallableListHelper(this, e);
	}

private:
	// template helper to avoid code duplication in doFindCallableList
	template <typename T>
	static auto doFindCallableListHelper(T * self, const Event & e)
		-> typename std::conditional<std::is_const<T>::value, const CallbackList_ *, CallbackList_ *>::type
	{
		std::lock_guard<Mutex> lockGuard(self->listenerMutex);

		auto it = self->eventCallbackListMap.find(e);
		if(it != self->eventCallbackListMap.end()) {
			return &it->second;
		}
		else {
			return nullptr;
		}
	}

private:
	// Mixin related
	struct DoMixinBeforeDispatch
	{
		template <typename T, typename Self, typename ...A>
		static auto forEach(const Self * self, A && ...args)
			-> typename std::enable_if<HasFunctionMixinBeforeDispatch<T, A...>::value, bool>::type {
			return static_cast<const T *>(self)->mixinBeforeDispatch(std::forward<A>(args)...);
		}

		template <typename T, typename Self, typename ...A>
		static auto forEach(const Self * /*self*/, A && ... /*args*/)
			-> typename std::enable_if<! HasFunctionMixinBeforeDispatch<T, A...>::value, bool>::type {
			return true;
		}
	};

private:
	Map eventCallbackListMap;
	mutable Mutex listenerMutex;
};


} //namespace internal_

template <
	typename Event_,
	typename Prototype_,
	typename Policies_ = DefaultPolicies
>
class EventDispatcher : public internal_::InheritMixins<
		internal_::EventDispatcherBase<Event_, Prototype_, Policies_, void>,
		typename internal_::SelectMixins<Policies_, internal_::HasTypeMixins<Policies_>::value >::Type
	>::Type, public TagEventDispatcher
{
private:
	using super = typename internal_::InheritMixins<
		internal_::EventDispatcherBase<Event_, Prototype_, Policies_, void>,
		typename internal_::SelectMixins<Policies_, internal_::HasTypeMixins<Policies_>::value >::Type
	>::Type;

public:
	using super::super;
	
	friend void swap(EventDispatcher & first, EventDispatcher & second) noexcept {
		first.swap(second);
	}
};

} //namespace eventpp
