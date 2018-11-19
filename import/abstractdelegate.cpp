/*
 *   Copyright 2018 by Marco Martin <mart@kde.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "abstractdelegate.h"
#include "mycroftcontroller.h"

AbstractDelegate::AbstractDelegate(QQuickItem *parent)
    : QQuickItem(parent)
{
    m_contentItem = new QQuickItem(this);
}

AbstractDelegate::~AbstractDelegate()
{
}

void AbstractDelegate::contentData_append(QQmlListProperty<QObject> *prop, QObject *object)
{
    AbstractDelegate *delegate = static_cast<AbstractDelegate *>(prop->object);
    if (!delegate) {
        return;
    }
qWarning()<<"AAAA"<<prop<<object<<prop->object;
    QQuickItem *item = qobject_cast<QQuickItem *>(object);
    delegate->m_contentData.append(object);
    if (item) {
        item->setParentItem(delegate->m_contentItem);
    }
}

int AbstractDelegate::contentData_count(QQmlListProperty<QObject> *prop)
{
    AbstractDelegate *delegate = static_cast<AbstractDelegate *>(prop->object);
    if (!delegate) {
        return 0;
    }

    return delegate->m_contentData.count();
}

QObject *AbstractDelegate::contentData_at(QQmlListProperty<QObject> *prop, int index)
{
    AbstractDelegate *delegate = static_cast<AbstractDelegate *>(prop->object);
    if (!delegate) {
        return nullptr;
    }

    if (index < 0 || index >= delegate->m_contentData.count()) {
        return nullptr;
    }
    return delegate->m_contentData.value(index);
}

void AbstractDelegate::contentData_clear(QQmlListProperty<QObject> *prop)
{
    AbstractDelegate *delegate = static_cast<AbstractDelegate *>(prop->object);
    if (!delegate) {
        return;
    }

    return delegate->m_contentData.clear();
}

QQmlListProperty<QObject> AbstractDelegate::contentData()
{
    return QQmlListProperty<QObject>(this, nullptr,
                                     contentData_append,
                                     contentData_count,
                                     contentData_at,
                                     contentData_clear);
}

void AbstractDelegate::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    m_contentItem->setX(m_leftPadding);
    m_contentItem->setY(m_topPadding);
    m_contentItem->setWidth(newGeometry.width() - m_leftPadding - m_rightPadding);
    m_contentItem->setHeight(newGeometry.width() - m_topPadding - m_bottomPadding);
    
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

void AbstractDelegate::setSessionData(SessionDataMap *data)
{
    //possible to call only once, by the skillview upon instantiation
    Q_ASSERT(!m_data);
    m_data = data;
}

SessionDataMap *AbstractDelegate::sessionData() const
{
    return m_data;
}

void AbstractDelegate::setQmlUrl(const QUrl &url)
{
    Q_ASSERT(m_qmlUrl.isEmpty());
    m_qmlUrl = url;
}

QUrl AbstractDelegate::qmlUrl() const
{
    return m_qmlUrl;
}

void AbstractDelegate::setSkillId(const QString &skillId)
{
    Q_ASSERT(m_skillId.isEmpty());
    m_skillId = skillId;
}

QString AbstractDelegate::skillId() const
{
    return m_skillId;
}

#include "moc_abstractdelegate.cpp"
