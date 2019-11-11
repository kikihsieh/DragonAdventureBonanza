#ifndef DAB_ANIMATABLE_HPP
#define DAB_ANIMATABLE_HPP

#include <common.hpp>
#include <map>
#include <string>
#include <memory>

typedef std::map<int, const char*> TexturePathMapping;
typedef std::map<int, std::shared_ptr<Texture>> TextureMapping;

struct Animatable {
    Animatable() {}
//        for (auto &iter : mapping) {
//            auto *texture = new Texture();
//            if (!texture->is_valid()) {
//                if (!texture->load_from_file(iter.second)) {
//                    fprintf(stderr, "Failed to load tile texture!");
//                    return;
//                }
//            }
//            m_texture_mapping.insert(TextureMapping::value_type(iter.first, texture));
//        }
//    }

    ~Animatable() {
    }

//    TextureMapping m_texture_mapping;
    int index = 0;
    float frame_switch_time = 80.f; // time in ms before frame should be switched
    float countdown = frame_switch_time;
    vec2 frame_index;
    int num_rows;
    int num_columns;
};
#endif //DAB_ANIMATABLE_HPP
