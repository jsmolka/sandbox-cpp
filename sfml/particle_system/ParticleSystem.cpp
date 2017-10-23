#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(unsigned int count) :
m_particles(count),
m_vertices(sf::Points, count),
m_lifetime(sf::seconds(3)),
m_emitter(0, 0)
{
}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
    m_emitter = position;
}

void ParticleSystem::update(sf::Time elapsed)
{
    for (std::size_t i = 0; i < m_particles.size(); i++)
    {
        // Update the particle lifetime
        Particle &p = m_particles[i];
        p.lifetime -= elapsed;

        // Respawn particle if dead
        if (p.lifetime <= sf::Time::Zero)
            resetParticle(i);

        // Update the position of the corresponding vertex
        m_vertices[i].position += p.velocity * elapsed.asSeconds();

        // Update the alpha (transparency) of the particle according to its lifetime
        float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
        m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Apply the transform
    states.transform *= getTransform();

    // Our particles don't use a texture
    states.texture = NULL;

    // Draw the vertex array
    target.draw(m_vertices, states);
}

void ParticleSystem::resetParticle(std::size_t index)
{
    // Give a random velocity and lifetime to the particle
    float angle = (std::rand() % 360) * 3.14f / 180.f;
    float speed = (std::rand() % 50) + 50.f;
    m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

    // Reset the position of the corresponding vertex
    m_vertices[index].position = m_emitter;
}
