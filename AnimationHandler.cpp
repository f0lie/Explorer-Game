//
// Created by alex on 4/13/16.
//

#include "AnimationHandler.h"

void AnimationHandler::update(const float dt)
{
    if (m_currentAnim >= m_animations.size() || m_currentAnim < 0)
    {
        return;
    }

    float duration = m_animations[m_currentAnim].m_duration;

    /*
     * Check if the animation has progressed to a new frame
     * and if so change to the next frame.
     */
    if (int((m_t + dt) / duration) > int(m_t / duration))
    {
        // Calculate the frame number
        int frame = int((m_t + dt) / duration);

        // Adjust for looping
        frame %= m_animations[m_currentAnim].getLength();

        /*
         * Set the sprite to the new frame.
         * Width the frame number.
         * Height is the animation.
         */
        sf::IntRect rect = m_frameSize;
        rect.left = rect.width * frame;
        rect.top = rect.height * m_currentAnim;
        m_bounds = rect;
    }

    m_t += dt;

    // Adjust for looping
    if (m_t > duration * m_animations[m_currentAnim].getLength())
    {
        m_t = 0.0f;
    }
}

void AnimationHandler::addAnim(Animation &anim)
{
    m_animations.push_back(anim);
}

void AnimationHandler::changeAnim(unsigned int animID)
{
    /*
     * Do not change the animation if the animation is currently active or
     * the new animation doesn't exist
     */
    if (m_currentAnim == animID || animID >= m_animations.size() || animID < 0)
    {
        return;
    }

    // Set the current animation
    m_currentAnim = animID;
    // Update the animation bounds
    sf::IntRect rect = m_frameSize;
    rect.top = rect.height * animID;
    m_bounds = rect;
    m_t = 0.0f;
}