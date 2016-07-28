#include "person.h"

void Person::setDisplayName(const QString displayname)
{
    m_displayName = displayname;
    emit displayNameChanged(m_displayName);
}

void Person::setAvatar(const QUrl avatar)
{
    m_avatar = avatar;
    emit avatarChanged(m_avatar);
}
