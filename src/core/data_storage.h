#pragma once

#include <string>
#include <memory>
#include <vector>
#include <cassert>

class state_storage
{
	struct value_base
	{
		value_base() noexcept {}
		value_base(const value_base &) = delete;
		value_base(value_base && value) noexcept
		{
			// all derived classes has same size (sizeof(StoredValue)==sizeof(StoredValueBase))
			std::memcpy(static_cast<void*>(this), static_cast<void*>(&value), sizeof(value_base));
			value.object = nullptr;
		}

		value_base & operator=(value_base && value) noexcept
		{
			release();
			assert(object == nullptr);
			std::memcpy(static_cast<void*>(this), static_cast<void*>(&value), sizeof(value_base));
			value.object = nullptr;
			return *this;
		}

		virtual ~value_base() noexcept { assert(object == nullptr); }
		virtual void release() noexcept {}

		template<class T>
		T* get() noexcept
		{
			return reinterpret_cast<T*>(object);
		}

		static size_t& next_type_index() noexcept
		{
			static size_t nextTypeIndex = 0;
			return nextTypeIndex;
		}

		void* object = nullptr;
	};

	template<class T>
	struct value_stored : public value_base
	{
		value_stored(std::unique_ptr<T>&& value)
		{
			static_assert(sizeof(value_stored) == sizeof(value_base), "The size of value_stored should be the same as value_base.");
			assert(value);
			managedObject = value.release();
		}

		void release() noexcept override
		{
			if (managedObject) {
				delete get<T>();
				managedObject = nullptr;
			}
		}

		~value_stored() noexcept override
		{
			value_stored<T>::release();
		}
	};

private:
	template<class T>
	value_base& get_stored_value() noexcept
	{
		size_t typeIndex = get_type_index<T>();

		if (_values.size() <= typeIndex) {
			_values.resize(typeIndex + 1);
		}

		return _values[typeIndex];
	}

	template<class T>
	value_base* find_stored_value() noexcept
	{
		size_t typeIndex = get_type_index<T>();

		if (_values.size() > typeIndex) {
			return &(_values[typeIndex]);
		}

		return nullptr;
	}

	template<class T>
	static size_t get_type_index() noexcept
	{
		return get_type_index_inner<std::remove_const_t<T>>();
	}

	template<class T>
	static size_t get_type_index_inner() noexcept
	{
		static size_t typeIndex = StoredValueBase::GetNextTypeIndex()++;
		return typeIndex;
	}

public:
	template<class T>
	void set(std::unique_ptr<T>&& resource) noexcept
	{
		auto&& value = GetStoredValue<T>();

		value = StoredValue<T>(std::move(resource));
	}

	template<class T>
	void remove() noexcept
	{
		auto store = find_stored_value<T>();
		if (store) {
			store->release();
		}
	}

	template<class T>
	T* find_value() noexcept
	{
		auto store = find_stored_value<T>();
		return store ? store->template get<T>() : nullptr;
	}

	template<class T>
	void move_value_from(state_storage & other) noexcept
	{
		if (this == &other) {
			return;
		}

		auto store = other.find_stored_value<T>();

		if (store) {
			set<T>(std::unique_ptr<T>(store->template get<T>()));
			store->object = nullptr;
		}
	}

	void remove_all() noexcept
	{
		_values.clear();
	}

private:
	std::vector<value_base> _values;
};
