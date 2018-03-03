#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(unsigned int count) :
mParticles(count),
mVertices(sf::Points, count),
mLifetime(sf::seconds(3)),
mEmitter(0, 0)
{
}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
    mEmitter = position;
}

void ParticleSystem::update(sf::Time elapsed)
{
    for (std::size_t i = 0; i < mParticles.size(); i++)
    {
        // Update the particle lifetime
        Particle &particle = mParticles[i];
        particle.lifetime -= elapsed;

        // Respawn particle if dead
        if (particle.lifetime <= sf::Time::Zero)
            resetParticle(i);

        // Update the position of the corresponding vertex
        mVertices[i].position += particle.velocity * elapsed.asSeconds();

        // Update the alpha (transparency) of the particle according to its lifetime
        float ratio = particle.lifetime.asSeconds() / mLifetime.asSeconds();
        mVertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Apply the transform
    states.transform *= getTransform();

    // Our particles don't use a texture
    states.texture = NULL;

    // Draw the vertex array
    target.draw(mVertices, states);
}

void ParticleSystem::resetParticle(std::size_t index)
{
    // Give a random velocity and lifetime to the particle
    float angle = (std::rand() % 360) * 3.14f / 180.f;
    float speed = (std::rand() % 50) + 50.f;
    mParticles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    mParticles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

    // Reset the position of the corresponding vertex
    mVertices[index].position = mEmitter;
}
