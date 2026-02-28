#include "cart_images.h"

#include "core/stable_array.h"

struct carrier_image_desc : public image_desc {
    e_resource resource;
};

template<>
struct stable_array_max_elements<carrier_image_desc> {
    enum { max_elements = RESOURCES_MAX };
};

template<>
struct std::hash<carrier_image_desc> {
    [[nodiscard]] size_t operator()(const carrier_image_desc &desc) const noexcept {
        return desc.resource;
    }
};

ANK_CONFIG_STRUCT(carrier_image_desc, resource, pack, id, offset)

stable_array<carrier_image_desc> ANK_VARIABLE(cart_images);
stable_array<carrier_image_desc> ANK_VARIABLE(sled_images);

template<typename T>
image_desc resource2carrier(e_resource resource_id, const T& images) {
    image_desc ret = images[resource_id];
    if (ret.pack && ret.id) {
        return ret;
    }

    return cart_images[RESOURCE_NONE];
}

image_desc resource2cart(e_resource resource_id) {
    return resource2carrier(resource_id, cart_images);
}

image_desc resource2sled(e_resource resource_id) {
    return resource2carrier(resource_id, sled_images);
}