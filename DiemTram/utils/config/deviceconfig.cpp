
#include "deviceconfig.h"
#include <qfile.h>
#include <qtextstream.h>
#include <qstringlist.h>
#include <iostream>

using namespace core::utils::config;

DeviceCfgGroup::DeviceCfgGroup( const QString & name ) :
  groupName( name )
{
}

DeviceCfgGroup::~DeviceCfgGroup()
{
}

void
DeviceCfgGroup::remove( const QString & key )
{
  if (map.contains(key))
  {
    map.remove( key );
  }
}

bool
DeviceCfgGroup::contains( const QString & key )
{
  return map.contains( key );
}

void
DeviceCfgGroup::setString( const QString & key, const QString & val )
{
  map.insert( key, val );
}

QString
DeviceCfgGroup::getString( const QString & key, const QString & def )
{
  if (map.contains( key ))
  {
    return map[key];
  }
  else
  {
    setString( key, def );
  }

  return def;
}

void
DeviceCfgGroup::setInt( const QString & key, int val )
{
  QString tmp;
  tmp.setNum( val );
  setString( key, tmp );
}

int
DeviceCfgGroup::getInt( const QString & key, int def )
{
  if (map.contains( key ))
  {
    return map[key].toInt();
  }
  else
  {
    setInt( key, def );
  }

  return def;
}

void
DeviceCfgGroup::setDouble( const QString & key, double val )
{
  QString tmp;
  tmp.setNum( val );
  setString( key, tmp );
}

double
DeviceCfgGroup::getDouble( const QString & key, double def )
{
  if (map.contains( key ))
  {
    return map[key].toDouble();
  }
  else
  {
    setDouble( key, def );
  }

  return def;
}

void
DeviceCfgGroup::setBool( const QString & key, bool val )
{
  setString( key, val ? "true" : "false" );
}

bool
DeviceCfgGroup::getBool( const QString & key, bool def )
{
  if (map.contains( key ))
  {
    QString val = map[key].toLower();

    if (val == "true" || val == "1" || val == "yes" || val == "on") return true;
    return false;
  }
  else
  {
    setBool( key, def );
  }

  return def;
}

DeviceCfg::DeviceCfg( const QString & name ) :
    fname( name )
{
}

DeviceCfg::~DeviceCfg()
{
  clear();
}

void
DeviceCfg::remove( const QString & group, const QString & key )
{
  if (map.contains(group))
  {
    map[group]->remove( key );
  }
}

void
DeviceCfg::remove( const QString & group )
{
  if (map.contains(group))
  {
    delete map[group];
    map.remove( group );
  }
}

bool
DeviceCfg::load()
{
    QFile file (fname);

  QString group;

  if (file.open(QIODevice::ReadOnly ))
  {
    clear();

    char *buf = new char [1000];

    while (file.readLine( buf, 999 ) != -1)
    {
      QString line = QString( buf ).trimmed();
      line = line.simplified();

      // Check if comment (good old assembler line comments:)
      //
      if (line.left(1) != "#" && line.left(1) != ";")
      {
        // Check for group
        //
        if (line.left(1) == "[")
        {
          group = line.mid( 1, line.length()-2 );
          add( group );
        }
        else
        {
          // Search '='
          //
          int pos;

          if ((pos = line.indexOf( '=')) != -1)
          {
            QString key = line.left( pos-1 );
            QString val;

            if ((int)line.length()-pos-2 > 0)
              val = line.right( line.length()-pos-2 );
            else
              val = "";

            setString( group, key, val );
          }
        }
      }
    }

    file.close();

  }
  else
  {
    return false;
  }

  return true;
}

bool
DeviceCfg::save()
{
  QFile file( fname );

  if (file.open( QIODevice::WriteOnly ))
  {
    QTextStream s(&file);

    QMap<QString,DeviceCfgGroup *>::Iterator it;


    for (it=map.begin(); it != map.end(); ++it)
    {
      s << "[";
      s << it.value()->name();
      s << "]\n";

      QMap<QString,QString>::Iterator itg;

      for (itg=it.value()->begin(); itg != it.value()->end(); ++itg)
      {
        s << itg.key();
        s <<  " = ";
        s << itg.value();
        s << "\n";
      }

      s << "\n";
    }
    file.close();
  }
  else
  {
    return false;
  }

  return true;
}

bool
DeviceCfg::contains( const QString & group )
{
  return map.contains( group );
}

bool
DeviceCfg::contains( const QString & group, const QString & key )
{
  if (map.contains( group ))
  {
    return map[group]->contains( key );
  }

  return false;
}

void
DeviceCfg::add( const QString & group )
{
  if (map.contains( group )) return;

  DeviceCfgGroup *g = new DeviceCfgGroup( group );
  map.insert( group, g );
}

void
DeviceCfg::setString( const QString & group, const QString & key,
                      const QString & val )
{
  if (map.contains( group ))
  {
    map[group]->setString( key, val );
  }
  else
  {
    DeviceCfgGroup *g = new DeviceCfgGroup( group );
    g->setString( key, val );

    map.insert( group, g );
  }
}

QString
DeviceCfg::getString( const QString & group, const QString & key,
                      const QString & def )
{
  if (map.contains( group ))
  {
    DeviceCfgGroup *g = map[group];

    return g->getString( key, def );
  }
  else
  {
    DeviceCfgGroup *g = new DeviceCfgGroup( group );
    g->setString( key, def );

    map.insert( group, g );
  }

  return def;
}

void
DeviceCfg::setInt( const QString & group, const QString & key,
                   int val )
{
  QString tmp;
  tmp.setNum( val );
  setString( group, key, tmp );
}

int
DeviceCfg::getInt( const QString & group, const QString & key,
                   int def )
{
  if (map.contains( group ))
  {
    DeviceCfgGroup *g = map[group];

    return g->getInt( key, def );
  }
  else
  {
    DeviceCfgGroup *g = new DeviceCfgGroup( group );
    g->setInt( key, def );

    map.insert( group, g );
  }

  return def;
}

void
DeviceCfg::setDouble( const QString & group, const QString & key,
                      double val )
{
  QString tmp;
  tmp.setNum( val );
  setString( group, key, tmp );
}

double
DeviceCfg::getDouble( const QString & group, const QString & key,
                      double def )
{
  if (map.contains( group ))
  {
    DeviceCfgGroup *g = map[group];

    return g->getDouble( key, def );
  }
  else
  {
    DeviceCfgGroup *g = new DeviceCfgGroup( group );
    g->setDouble( key, def );

    map.insert( group, g );
  }

  return def;
}

void
DeviceCfg::setBool( const QString & group, const QString & key,
                    bool val )
{
  setString( group, key, val ? "true" : "false" );
}

bool
DeviceCfg::getBool( const QString & group, const QString & key,
                    bool def )
{
  if (map.contains( group ))
  {
    DeviceCfgGroup *g = map[group];

    return g->getBool( key, def );
  }
  else
  {
    DeviceCfgGroup *g = new DeviceCfgGroup( group );
    g->setBool( key, def );

    map.insert( group, g );
  }

  return def;
}

void
DeviceCfg::clear()
{
  QMap<QString,DeviceCfgGroup *>::Iterator it;

  for (it=map.begin(); it != map.end(); ++it)
  {
    delete it.value();
  }

  map.clear();
}

void
DeviceCfg::removeEmpty()
{
  QMap<QString,DeviceCfgGroup *>::Iterator git;

  QStringList list;

  for (git=map.begin(); git != map.end(); ++git)
  {
    QMap<QString,QString>::Iterator kit;

    list.clear();

    for (kit=git.value()->begin(); kit != git.value()->end(); ++kit)
    {
      if (kit.value().isEmpty())
      {
        // value is empty -> shedule for removal
        list.append( kit.key() );
      }
    }

    // Now remove empty keys
    for (QStringList::Iterator rit=list.begin(); rit != list.end(); ++rit )
    {
      git.value()->remove( *rit );
    }
  }
}

