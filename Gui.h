//
// Created by alex on 4/15/16.
//

#ifndef LEGEND_OF_THE_SWAMP_GUISTYLE_H
#define LEGEND_OF_THE_SWAMP_GUISTYLE_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <utility>
#include <string>

struct GuiStyle
{
    sf::Color m_bodyCol;
    sf::Color m_bodyHighlightCol;

    sf::Color m_borderCol;
    sf::Color m_borderHighlightCol;

    sf::Color m_textCol;
    sf::Color m_textHighlightCol;

    sf::Font *m_font;

    float m_borderSize;

    GuiStyle() = default;

    GuiStyle(sf::Font *font, float borderSize, const sf::Color &bodyCol, const sf::Color &borderCol,
             const sf::Color &textCol, const sf::Color &bodyHighlightCol, const sf::Color &borderHighlightCol,
             const sf::Color &textHighlightCol) : m_bodyCol(bodyCol),
                                                  m_bodyHighlightCol(bodyHighlightCol),
                                                  m_borderCol(borderCol),
                                                  m_borderHighlightCol(borderHighlightCol),
                                                  m_textCol(textCol),
                                                  m_textHighlightCol(textHighlightCol),
                                                  m_font(font),
                                                  m_borderSize(borderSize) { }
};

struct GuiEntry
{
    // Handles appearance of the entry
    sf::RectangleShape m_shape;

    // String returned when entry is activated
    std::string m_message;

    // Test displayed on the entry
    sf::Text m_text;

    GuiEntry() = default;

    GuiEntry(const std::string &message, const sf::RectangleShape &shape, const sf::Text &text) : m_shape(shape),
                                                                                                  m_message(message),
                                                                                                  m_text(text) { }
};

class Gui : public sf::Transformable, public sf::Drawable
{
public:
    std::vector<GuiEntry> m_entries;
    bool m_visable;

    Gui(const sf::Vector2f &dimensions, int padding, bool horizontal, const GuiStyle &style,
        const std::vector<std::pair<std::string, std::string>> &entries);

    /*
     * Return the index of the entry the mouse is hovering over.
     * If the mouse is outside of the GUI, return -1.
     */
    int getEntry(const sf::Vector2f mousePos);

    /* Change the text of an entry. */
    void setEntryText(int entry, const std::string &text);

    /* Change the entry dimensions. */
    void setDimensions(sf::Vector2f dimensions);

    /* Draw the menu. */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /* Make the GUI visable and position the entries correctly */
    void show();

    void hide();

    /* Highlights an entry of the menu. */
    void highlight(const int entry);

    /* Return the message bound to the entry. */
    std::string activate(const int entry);

    std::string activate(const sf::Vector2f mousePos);

private:
    // Display entries vertically unless horizontal flag is true
    bool m_horizontal;
    GuiStyle m_style;
    sf::Vector2f m_dimensions;
    int m_padding;
};


#endif //LEGEND_OF_THE_SWAMP_GUISTYLE_H
