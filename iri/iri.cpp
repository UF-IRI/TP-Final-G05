#pragma once

#include <string>
#include <cstring>
#include <regex>

std::string BASE_PATH = "..\\..\\..\\";
std::string FOLDER_PATH = "data_files\\input\\";

// Expresiones Regulares (REGEX)

    // Expresion regular para numeros
    // Devuelve 1 Grupo
    // "1235"
    std::string reg_numero = "(\\d+)";

    // Expresion regular para palabras
    // Devuelve 1 Grupo
    // ie:
    // "Hello World"
    std::string reg_palabra = "(\\w|\\s{1,})";

    // Expresion regular para fechas (dd/mm/yyyy :: dia/mes/año)
    // Devuelve 4 Grupo
    // ie:
    // Grupo 1 >> "09/12/2018"
    // Grupo 2 >> "09"
    // Grupo 3 >> "12"
    // Grupo 4 >> "2018"
    std::string reg_fecha = "(([0-2][0-9]|3[0-1])\\/(0[0-9]|1[0-2])\\/(\\d{4}))";

    // Expresion regular para matricula medico
    // Devuelve 1 Grupo
    // ie:
    // "12-4546-123"
    std::string reg_matricula_medico = "(\\d+\\-\\d+\\-\\d+)";

    // Expresion regular para telefono/celular
    // Devuelve 1 Grupo
    // ie:
    
    std::string reg_telefono = "(\\+54\\s\\(\\d+\\)\\s\\d+)";

    // Expresion regular para mail
    // Cantidad de valores 1
    std::string reg_mail = "(\\w+\\@\\w+\\.\\w+)";

    // Expresion regular para booleano
    // Cantidad de valores 1
    std::string reg_booleano = "(\\d)";

    bool regex_2_bool(std::string regex_value) {
        return std::stoi(regex_value) ? true : false;
    }