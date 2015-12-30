/* 
 * File:   main.cpp
 * Author: mike
 *
 * Created on 29 декабря 2015 г., 17:07
 */

#include <libintl.h>
#include <locale.h>
#include <stdio.h> 
#include <stdlib.h>
#include <SimpleIni.h>
#include <string>

#define _(String) gettext(String)

int main()
{
    
    CSimpleIniA ini;
    ini.SetMultiKey(true);
    ini.LoadFile("config.ini");
    
    CSimpleIniA::TNamesDepend ini_locale_path;
    ini.GetAllValues("locale_path", "path", ini_locale_path);
    CSimpleIniA::TNamesDepend ini_locale_name;
    ini.GetAllValues("locale_name", "lang", ini_locale_name);
    CSimpleIniA::TNamesDepend ini_locale_codeset;
    ini.GetAllValues("locale_codeset", "codeset", ini_locale_codeset);
    
    printf(ini_locale_path.begin()->pItem);
    printf("\n");
    printf(ini_locale_name.begin()->pItem);
    printf("\n");
#ifdef _WIN
    std::string temp_str("LANG=");
#else 
    std::string temp_str("LANGUAGE=");
#endif
    temp_str.append(ini_locale_name.begin()->pItem);
     
    std::string locale_path(ini_locale_path.begin()->pItem);
    std::string locale_name(temp_str);
    std::string locale_codeset(ini_locale_codeset.begin()->pItem);
    
#ifndef _WIN
    char *temp_char_buf = new char[locale_name.length()+1];
    strcpy(temp_char_buf, locale_name.c_str() );
    putenv(temp_char_buf);
#else
    putenv(locale_name.c_str());
#endif
    setlocale(LC_ALL,"");

    textdomain("helloworld");
    bindtextdomain("helloworld",locale_path.c_str());
    bind_textdomain_codeset("helloworld", locale_codeset.c_str() );
    
    printf(_("Hello World\n"));

    delete temp_char_buf;
    return 0;
}