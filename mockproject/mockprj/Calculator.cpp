#include "Calculator.hpp"
#include <QtMath>

Calculator::Calculator(QObject *parent)
    : QObject(parent),
      m_display("0"),
      m_subDisplay(""),
      m_leftOperand(0.0),
      m_waitingForOperand(true),
      m_doneCalculate(true)
{
    m_buttons = {
        "C", "÷",
        "7", "8", "9", "×",
        "4", "5", "6", "-",
        "1", "2", "3", "+",
        "0", ".",       "="
    };

    for (const QVariant &i : m_buttons) {
        QString temp = i.toString();
        if (temp == "C" || temp == "=") {
            m_colors.append("orange");
            m_buttonhoveredcolors.append("lightsalmon");
            m_buttonpressedcolors.append("darkorange");
        }
        else {
            m_colors.append("white");
            m_buttonhoveredcolors.append("gainsboro");
            m_buttonpressedcolors.append("silver");
        }
    }

    for (const QVariant &i : m_buttons) {
        QString temp = i.toString();
        if (temp == "C") {
            m_buttonlayout.append(3);
            m_buttoniconsource.append("c.png");
            m_buttontxtvisible.append(false);
        }
        else if (temp == "=") {
            m_buttonlayout.append(2);
            m_buttoniconsource.append("");
            m_buttontxtvisible.append(true);
        }
        else {
            m_buttonlayout.append(1);
            m_buttoniconsource.append("");
            m_buttontxtvisible.append(true);
        }
    }
}

void Calculator::buttonClicked(const QString &text)
{
    if (text == "C") {
        clear();
        return;
    }


    if (text == "+" || text == "-" || text == "×" || text == "÷") {
        m_leftOperand = m_display.toDouble();
        m_pendingOperator = text;
        m_subDisplay = QString("%1 %2").arg(m_display, text);
        emit subDisplayChanged();
        m_waitingForOperand = true;
        m_doneCalculate = false;
        return;
    }

    if (text == "=") {

        if ((!m_doneCalculate && m_waitingForOperand) || (m_subDisplay != "" && !m_doneCalculate))
            if (m_display != "Error")
                m_subDisplay = QString("%1 %2 %3 %4").arg(QString::number(m_leftOperand), m_pendingOperator, m_display, "=");

        double rightOperand = m_display.toDouble();
        calculate(rightOperand, m_pendingOperator);
        m_pendingOperator.clear();
        emit subDisplayChanged();
        return;
    }


    if (text == ".") {
        if (!m_display.contains("."))
            m_display += ".";
        m_doneCalculate = false;
        emit displayChanged();
        return;
    }

    bool isNumber = (text >= "0" && text <= "9");
    if (isNumber) {
        if (m_display == "0" || m_waitingForOperand) {
            m_display = text;
            m_waitingForOperand = false;
        } else {
            m_display += text;
        }
        if (m_doneCalculate) {
            m_subDisplay.clear();
            emit subDisplayChanged();
        }

        m_doneCalculate = false;
        emit displayChanged();
        return;
    }
}

void Calculator::clear()
{
    m_display = "0";
    m_subDisplay.clear();
    m_leftOperand = 0.0;
    m_pendingOperator.clear();
    m_waitingForOperand = true;
    m_doneCalculate = true;
    emit displayChanged();
    emit subDisplayChanged();
}

void Calculator::calculate(double rightOperand, const QString &op)
{
    if (op.isEmpty()) return;

    double result = 0.0;

    if (op == "+")
        result = m_leftOperand + rightOperand;
    else if (op == "-")
        result = m_leftOperand - rightOperand;
    else if (op == "×")
        result = m_leftOperand * rightOperand;
    else if (op == "÷") {
        if (rightOperand == 0.0) {
            m_display = "Error";
            emit displayChanged();
            return;
        }
        result = m_leftOperand / rightOperand;
    }

    m_display = QString::number(result);
    emit displayChanged();
    m_leftOperand = result;
    m_waitingForOperand = true;
    m_doneCalculate = true;
}
