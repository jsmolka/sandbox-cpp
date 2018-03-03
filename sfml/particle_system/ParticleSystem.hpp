#ifndef PARTICLE_SYSTEM_PARTICLESYSTEM_HPP
#define PARTICLE_SYSTEM_PARTICLESYSTEM_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    explicit ParticleSystem(unsigned int count);
    void setEmitter(sf::Vector2f position);
    void update(sf::Time elapsed);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };
    void resetParticle(std::size_t index);

    std::vector<Particle> mParticles;
    sf::VertexArray mVertices;
    sf::Time mLifetime;
    sf::Vector2f mEmitter;
};

#endif //PARTICLE_SYSTEM_PARTICLESYSTEM_HPP
