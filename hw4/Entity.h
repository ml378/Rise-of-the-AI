#ifndef ENTITY_H
#define ENTITY_H

#include "glm/glm.hpp"
#include "ShaderProgram.h"

enum AnimationDirection { LEFT, RIGHT, UP, DOWN };

class Entity
{
private:
    // ����� TRANSFORMATIONS ����� //
    glm::vec3 m_movement;
    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::vec3 m_velocity;
    glm::vec3 m_acceleration;

    glm::mat4 m_model_matrix;

    float m_speed;
    float m_fuel = 200.0f;

    // ����� TEXTURES ����� //
    GLuint    m_texture_id;

    // ����� ANIMATION ����� //
    int m_animation_cols;
    int m_animation_frames,
        m_animation_index,
        m_animation_rows;

    int* m_animation_indices = nullptr;
    float m_animation_time = 0.0f;

    int m_width = 1,
        m_height = 1;

public:
    // ����� STATIC VARIABLES ����� //
    static constexpr int SECONDS_PER_FRAME = 4;

    // ����� METHODS ����� //
    Entity();
    Entity(GLuint texture_id, float speed, int walking[4][4], float animation_time,
        int animation_frames, int animation_index, int animation_cols,
        int animation_rows);
    Entity(GLuint texture_id, float speed); // Simpler constructor
    ~Entity();

    void draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index);
    bool const check_collision(Entity* other) const;

    void update(float delta_time, Entity* collidable_entities, int collidable_entity_count);
    void render(ShaderProgram* program);

    void normalise_movement() { m_movement = glm::normalize(m_movement); }

    void consume_fuel(float amount); 

    // ����� GETTERS ����� //
    glm::vec3 const get_position()     const { return m_position; }
    glm::vec3 const get_velocity()     const { return m_velocity; }
    glm::vec3 const get_acceleration() const { return m_acceleration; }
    glm::vec3 const get_movement()     const { return m_movement; }
    glm::vec3 const get_scale()        const { return m_scale; }
    GLuint    const get_texture_id()   const { return m_texture_id; }
    float     const get_speed()        const { return m_speed; }
    float     const get_fuel()         const { return m_fuel; }

    // ����� SETTERS ����� //
    void const set_position(glm::vec3 new_position) { m_position = new_position; }
    void const set_velocity(glm::vec3 new_velocity) { m_velocity = new_velocity; }
    void const set_acceleration(glm::vec3 new_acceleration) { m_acceleration = new_acceleration; }
    void const set_movement(glm::vec3 new_movement) { m_movement = new_movement; }
    void const set_scale(glm::vec3 new_scale) { m_scale = new_scale; }
    void const set_texture_id(GLuint new_texture_id) { m_texture_id = new_texture_id; }
    void const set_speed(float new_speed) { m_speed = new_speed; }
    void const set_animation_cols(int new_cols) { m_animation_cols = new_cols; }
    void const set_animation_rows(int new_rows) { m_animation_rows = new_rows; }
    void const set_animation_frames(int new_frames) { m_animation_frames = new_frames; }
    void const set_animation_index(int new_index) { m_animation_index = new_index; }
    void const set_animation_time(float new_time) { m_animation_time = new_time; }
};

#endif // ENTITY_H