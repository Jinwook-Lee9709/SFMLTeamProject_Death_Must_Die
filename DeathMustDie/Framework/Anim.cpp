#include "stdafx.h"
#include "Anim.h"

namespace fz {
    Anim::Anim(const std::string& name)
        : Activated(true)
        , Repeat(true)
        , m_Name(name)
        , m_Sprite(nullptr)
        , m_Texture(nullptr)
        , m_Frames()
        , m_Flips{false, false}
        , m_Scale{ 1.f, 1.f }
        , m_TotalLength(0.0)
        , m_TotalProgress(0.0)
        , m_IsEnd(false)
    {
        // Empty
    }

    Anim::~Anim()
    {
        // Empty
    }

    bool Anim::LoadFromFile(const std::string& path)
    {
        bool result = false;
        if (m_Texture)
            m_Texture.reset();

        m_Texture = std::make_unique<sf::Texture>();
        result = m_Texture->loadFromFile(path);
        if (result)
        {
            if (m_Sprite)
                m_Sprite.reset();

            m_Sprite = std::make_unique<sf::Sprite>();
            m_Sprite->setTexture(*m_Texture);
        }
        return result;
    }

    void Anim::AddFrame(const Frame& frame)
    {
        m_Frames.push_back(std::move(frame));
        m_TotalLength += frame.Duration;
    }

    void Anim::SetName(const std::string& name)
    {
        m_Name = name;
    }

    void Anim::SetPosition(const sf::Vector2f& pos)
    {
        if (m_Sprite != nullptr)
        {
            m_Sprite->setPosition(pos);
        }
    }

    void Anim::SetScale(const sf::Vector2f& scale)
    {
        m_Scale[0] = scale.x;
        m_Scale[1] = scale.y;
    }

    void Anim::SetScale(float scaleX, float scaleY)
    {
        this->SetScale({ scaleX, scaleY });
    }

    void Anim::SetFlipX(bool enabled)
    {
        m_Flips[0] = enabled;
    }

    void Anim::SetFlipY(bool enabled)
    {
        m_Flips[1] = enabled;
    }

    std::string Anim::GetName() const
    {
        return m_Name;
    }

    sf::Vector2f Anim::GetPosition() const
    {
        return m_Sprite->getPosition();
    }

    sf::Vector2f Anim::GetScale() const
    {
        return m_Sprite->getScale();
    }

    bool Anim::IsFlipX() const
    {
        return (m_Flips[0] < 0.0f) ? true : false;
    }

    bool Anim::IsFlipY() const
    {
        return (m_Flips[1] < 0.0f) ? true : false;
    }

    bool Anim::IsFrameEnd() const
    {
        return m_IsEnd;
    }

    void Anim::AddAnimSequence(
        const sf::IntRect& rect, 
        int stride, 
        const std::vector<double>& durations, 
        int count)
    {
        for (int i = 0; i < count; ++i)
        {
            auto x = rect.left;
            auto y = rect.top;
            auto width = rect.width;
            auto height = rect.height;

            x += i * (width + stride);
            m_Frames.push_back({ {x, y, width, height}, durations[i]});
        }
    }

    void Anim::AddAnimSequenceRev(
        const sf::IntRect& rect, 
        int stride, 
        const std::vector<double>& durations, 
        int count)
    {
        for (int i = count - 1; i >= 0; --i)
        {
            auto x = rect.left;
            auto y = rect.top;
            auto width = rect.width;
            auto height = rect.height;
            x += i * (width + stride);
            m_Frames.push_back({ {x, y, width, height}, durations[count - (i + 1)]});
        }
    }

    void Anim::AddAnimSequence(const sf::IntRect& rect, int stride, double duration, int count)
    {
        std::vector<double> durations(count, duration);
        this->AddAnimSequence(rect, stride, durations, count);
    }

    void Anim::AddAnimSequenceRev(const sf::IntRect& rect, int stride, double duration, int count)
    {
        std::vector<double> durations(count, duration);
        this->AddAnimSequenceRev(rect, stride, durations, count);
    }

    void Anim::SetAnimSequence(const sf::IntRect& rect, int stride, const std::vector<double>& durations, int count)
    {
        this->ClearSequence();
        this->AddAnimSequence(rect, stride, durations, count);
    }

    void Anim::SetAnimSequenceRev(const sf::IntRect& rect, int stride, const std::vector<double>& durations, int count)
    {
        this->ClearSequence();
        this->AddAnimSequenceRev(rect, stride, durations, count);
    }

    void Anim::SetAnimSequence(const sf::IntRect& rect, int stride, double duration, int count)
    {
        std::vector<double> durations(count, duration);
        this->SetAnimSequence(rect, stride, durations, count);
    }

    void Anim::SetAnimSequenceRev(const sf::IntRect& rect, int stride, double duration, int count)
    {
        std::vector<double> durations(count, duration);
        this->SetAnimSequenceRev(rect, stride, durations, count);
    }

    void Anim::Update(float dt)
    {
        m_TotalProgress += dt;

        double progress = m_TotalProgress;
        for (const auto& frame : m_Frames)
        {
            progress -= (frame).Duration;
            if (progress <= 0.0)
            {
                m_Sprite->setTextureRect((frame).Rect);
                break;
            }
            else if (&(frame) == &m_Frames.back())
            {
                if (Repeat || Activated)
                    this->Reset();
                else
                    m_Sprite->setTextureRect(m_Frames.front().Rect);
                m_IsEnd = true;
            }
        }
    }

    void Anim::Reset()
    {
        m_TotalProgress = 0.0;
        m_IsEnd = false;
    }

    void Anim::Draw(sf::RenderWindow& window)
    {
        if (!Activated)
            return;

        sf::Vector2f newScale;
        newScale.x = m_Scale[0] * ((m_Flips[0]) ? -1.0f : 1.0f);
        newScale.y = m_Scale[1] * ((m_Flips[1]) ? -1.0f : 1.0f);
        m_Sprite->setScale({ newScale.x, newScale.y });
        window.draw(*m_Sprite);
    }

    void Anim::ClearSequence()
    {
        m_Frames.clear();
        m_TotalLength = 0.0;
        m_TotalProgress = 0.0;
    }

} // namespace fz
