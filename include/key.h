#ifndef KEY_H
#define KEY_H

#include <QString>
#include <QIcon>
#include <QPushButton>
#include <QDebug>
class Key : public QPushButton {
    Q_OBJECT

    Q_PROPERTY(bool pressed READ isPressed WRITE setPressed)
    Q_PROPERTY(bool current READ isCurrent WRITE setCurrent)
    Q_PROPERTY(int keywidth READ getWidth WRITE setWidth)
    Q_PROPERTY(int keyheight READ getHeight WRITE setHeight)

public:
    // needed for move explicit Key() = delete;
    explicit Key(const QString &iText, const QString &iIcon = QString(), const int &iMinWidth = 24,
                 const int &iMinHeight = 24, QWidget *iParent = nullptr);
    // explicit Key(Key &&other) noexcept;    // mctor
    // explicit Key(const Key &);             // cctor

    ~Key() override = default;

    // Key &operator=(const Key &other);
    // Key &operator=(Key &&other) noexcept;

    const bool &isPressed() const;
    void setPressed(const bool &iState);

    const bool &isCurrent() const;
    void setCurrent(const bool &iState);

    int getWidth() const;
    void setWidth(const int &iWidth);

    int getHeight() const;
    void setHeight(const int &iHeight);

signals:
    void keyPressed();

public slots:
    void on_clicked() { emit keyPressed(); }

protected:
    void resizeEvent(QResizeEvent *iEvent) override;

private:
    // int _width = 24;     // From QWidget Property
    // int _height = 24;    // From QWidget Property
    int _xPos = 0;
    int _yPos = 0;
    // QString _text; // From QPushButton Property
    bool _isPressed = false;
    bool _isCurrent = false;

    static void computeNewFontSize(Key &ioKey);
};

#endif    // KEY_H
