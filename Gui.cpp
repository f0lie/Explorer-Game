//
// Created by alex on 4/15/16.
//

#include "Gui.h"

Gui::Gui(const sf::Vector2f &dimensions, int padding, bool horizontal, const GuiStyle &style,
         const std::vector<std::pair<std::string, std::string>> &entries) : m_visable(false),
                                                                            m_style(style),
                                                                            m_horizontal(horizontal),
                                                                            m_dimensions(dimensions),
                                                                            m_padding(padding)
{
    // Background shape
    sf::RectangleShape shape(dimensions);
    shape.setFillColor(m_style.m_bodyCol);
    shape.setOutlineThickness(-m_style.m_bordersize);
    shape.setOutlineColor(m_style.m_borderCol);

    // Gui entries
    for (const auto &entry : entries)
    {
        // Fit the text within the entity box;
        sf::Text text(entry.first, *style.m_font, m_dimensions.y - style.m_bordersize - padding);
        text.setColor(m_style.m_textCol);

        m_entries.push_back(GuiEntry(entry.second, shape, text));
    }
}

int Gui::getEntry(const sf::Vector2f mousePos)
{
    // If there are no entries then outside the menu
    if (m_entries.size() == 0) { return -1; }
    if (!m_visable) { return -1; }

    for (unsigned int i = 0; i < m_entries.size(); i++)
    {
        // Translate point to use the entry's local coordinates
        // Where (0,0) is the top left of the entry
        sf::Vector2f point = mousePos;
        point += m_entries[i].m_shape.getOrigin();
        point -= m_entries[i].m_shape.getPosition();

        if (point.x < 0 || point.x > m_entries[i].m_shape.getScale().x * m_dimensions.x) { continue; }
        if (point.y < 0 || point.y > m_entries[i].m_shape.getScale().y * m_dimensions.y) { continue; }
        return i;
    }

    return -1;
}

void Gui::setEntryText(int entry, const std::string &text)
{
    if (entry < 0 || entry > int(m_entries.size())) { return; }

    m_entries[entry].m_text.setString(text);
}

void Gui::setDimensions(sf::Vector2f dimensions)
{
    m_dimensions = dimensions;

    for (auto &entry : m_entries)
    {
        entry.m_shape.setSize(dimensions);
        entry.m_text.setCharacterSize(dimensions.y - m_style.m_bordersize - m_padding);
    }
}

void Gui::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (!m_visable) { return; }

    // Draw each entry of the menu
    for (const auto &entry : m_entries)
    {
        target.draw(entry.m_shape);
        target.draw(entry.m_text);
    }
}

void Gui::show()
{
    sf::Vector2f offset{0.0f, 0.0f};

    m_visable = true;

    // Calculate the correct position of each entry for drawing
    for (auto &entry : m_entries)
    {
        // Set the origin of the entry
        sf::Vector2f origin = getOrigin();
        origin -= offset;
        entry.m_shape.setOrigin(origin);
        entry.m_text.setOrigin(origin);

        // Compute the position of the entry
        entry.m_shape.setPosition(getPosition());
        entry.m_text.setPosition(getPosition());

        if (m_horizontal)
        {
            offset.x += m_dimensions.x;
        }
        else
        {
            offset.y += m_dimensions.y;
        }
    }
}

void Gui::hide()
{
    m_visable = false;
}

void Gui::highlight(const int entry)
{
    for (int i = 0; i < int(m_entries.size()); ++i)
    {
        if (i == entry)
        {
            // Highlight the right entry
            m_entries[i].m_shape.setFillColor(m_style.m_bodyHighlightCol);
            m_entries[i].m_shape.setOutlineColor(m_style.m_borderHighlightCol);
            m_entries[i].m_text.setColor(m_style.m_textHighlightCol);
        }
        else
        {
            // Un-highlight everyone else
            m_entries[i].m_shape.setFillColor(m_style.m_bodyCol);
            m_entries[i].m_shape.setOutlineColor(m_style.m_borderCol);
            m_entries[i].m_text.setColor(m_style.m_textCol);
        }
    }
}

std::string Gui::activate(const int entry)
{
    if (entry < 0) { return "null"; }
    return m_entries[entry].m_message;
}

std::string Gui::activate(const sf::Vector2f mousePos)
{
    int entry = getEntry(mousePos);
    return activate(entry);
}