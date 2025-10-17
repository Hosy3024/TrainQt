#ifndef CALCULATOR_H
#define CALCULATOR_H

#pragma once
#include <QObject>
#include <QString>
#include <QVariantList>

class Calculator : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString display READ display NOTIFY displayChanged)
    Q_PROPERTY(QString subDisplay READ subDisplay NOTIFY subDisplayChanged)
    Q_PROPERTY(QVariantList buttons READ buttons CONSTANT)
    Q_PROPERTY(QVariantList colors READ colors CONSTANT)
    Q_PROPERTY(QVariantList buttonlayout READ buttonlayout CONSTANT)
    Q_PROPERTY(QVariantList buttonhoveredcolors READ buttonhoveredcolors CONSTANT)
    Q_PROPERTY(QVariantList buttonpressedcolors READ buttonpressedcolors CONSTANT)
    Q_PROPERTY(QVariantList buttonicons READ buttonicons CONSTANT)

public:
    Calculator(QObject *parent = nullptr);

    QString display() const { return m_display; }
    QString subDisplay() const { return m_subDisplay; }
    QVariantList buttons() const { return m_buttons; }
    QVariantList colors() const { return m_colors; }
    QVariantList buttonlayout() const { return m_buttonlayout; }
    QVariantList buttonhoveredcolors() const { return m_buttonhoveredcolors; }
    QVariantList buttonpressedcolors() const { return m_buttonpressedcolors; }
    QVariantList buttonicons() const { return m_buttonicons; }

    Q_INVOKABLE void buttonClicked(const QString &text);

signals:
    void displayChanged();
    void subDisplayChanged();

private:
    QString m_display;
    QString m_subDisplay;

    double m_leftOperand;
    QString m_pendingOperator;
    bool m_waitingForOperand;
    bool m_doneCalculate;

    QVariantList m_buttons;
    QVariantList m_colors;
    QVariantList m_buttonlayout;
    QVariantList m_buttonhoveredcolors;
    QVariantList m_buttonpressedcolors;
    QVariantList m_buttonicons;

    void clear();
    void calculate(double rightOperand, const QString &op);
};


#endif // CALCULATOR_H
