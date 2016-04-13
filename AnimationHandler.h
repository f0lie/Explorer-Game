#ifndef LEGEND_OF_THE_SWAMP_ANIMATIONHANDLER_H
#define LEGEND_OF_THE_SWAMP_ANIMATIONHANDLER_H

#include <SFML/Graphics.hpp>

#include <vector>

struct Animation
{
    Animation(unsigned int startFrame, unsigned int endFrame, float duration) : m_startFrame(startFrame),
                                                                                m_endFrame(endFrame),
                                                                                m_duration(duration)
    { }

    unsigned int m_startFrame;
    unsigned int m_endFrame;
    float m_duration;

    unsigned int getLength() const noexcept
    { return m_endFrame - m_startFrame + 1; }
};

class AnimationHandler
{
public:
    AnimationHandler() : m_t(0.0f),
                         m_currentAnim(-1)
    { };

    AnimationHandler(const sf::IntRect &framesize) : m_frameSize(framesize),
                                                     m_t(0.0f),
                                                     m_currentAnim(-1)
    { };

    void addAnim(Animation &anim);

    /*
     * Update the current frame of the animation. dt is the time since
     * the update was last called (i.e. the time for one frame to be executed)
     */
    void update(const float dt);

    // Change the animation, resetting m_t in the process
    void changeAnim(unsigned int animID);

    // Current section of the txture that should be displayed
    sf::IntRect m_bounds;

    // Pixel dimensions of each individual frame
    sf::IntRect m_frameSize;

private:
    // Array of animations
    std::vector<Animation> m_animations;

    // Current time since the animation loop started
    float m_t;

    int m_currentAnim;
};


#endif //LEGEND_OF_THE_SWAMP_ANIMATIONHANDLER_H
