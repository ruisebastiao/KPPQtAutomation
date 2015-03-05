#include "menustyle.h"
#include <QFontMetrics>
#include <QApplication>

int MenuStyle::pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const {
    // Get size one em (text height in pixels)
    int em=QApplication::fontMetrics().height();

    // Return the size of menu item icons
    switch (metric) {
        case QStyle::PM_SmallIconSize: return 2.5*em;
        case QStyle::PM_LargeIconSize: return 2.5*em;
        default: return QProxyStyle::pixelMetric(metric, option, widget);
    }
}
