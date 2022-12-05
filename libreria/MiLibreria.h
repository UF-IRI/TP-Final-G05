/*
* 
* time_t convertDateToTimeT(string dato)
{
	int i = 0;
	int day, month, year;
	int cont = 0;
	string auxD{};
	string auxM{};
	string auxY{};
	string aux;
	int cont2 = 0;
	while (i < (dato.length() - 1))
	{

		while (dato[i] != '/')
		{

			if (cont == 0)
			{
				aux = dato[i];
				auxD += aux;
			}
			else if (cont == 1)
			{
				aux = dato[i];
				auxM += aux;
			}
			else
			{
				if (cont2 >= 4)
					break;
				aux = dato[i];
				auxY += aux;
				cont2++;
			}

			i++;

		}
		cont++;
		i++;
	}


	day = stoi(auxD);
	month = stoi(auxM);
	year = stoi(auxY);


	tm date{};
	date.tm_year = year - 1900;
	date.tm_mon = month - 1;
	date.tm_mday = day;

	time_t finalDate = mktime(&date);
	return finalDate;
}
//le doy una string y me la devuelve en time_t

void secretary(string SecretaryFileName, int sizeFile) //falta lo de escribir una nuesva consulta en el array de consultas
{//basicamente para secretaria abren por separado todas las listas para guardarse la data q fueron recopilando de los oarchivos originales
	//ahora bien cuando poseen esa data hacen for y con random generan las respuestas de los pacientes
	srand(NULL);
	int comeBack, change, answered, idInsurance;
	fstream fp;
	
	fp.open(SecretaryFileName, ios::in); //abro archivo de la secretaria para leer

	if (!(fp.is_open()))
		return;
	char comma = 0;
	string dummy;

	Pac* finalList = new Pac[sizeFile]; //nueva lista con el tamanio de la que me pasan en el archivo

	fp >> dummy >> comma >> dummy >> comma >> dummy >> comma >> dummy >> comma >> dummy >> comma >> dummy; //leo el encabezado
	int i = 0;
	while (fp)//cargo la lista con los datos
	{
		fp >> finalList[i].DNI >> comma >> finalList[i].firstName >> comma >> finalList[i].lastName >> comma >> finalList[i].Cont.celular >> 
			comma >> finalList[i].Cons.ensurance >> comma >> finalList[i].Cons.matriculaMed >> comma >> finalList[i].Cons.attendance; 
		//leo los datos en el array
		i++;
	}
	fp.close();
	//QUEDA CON EL PATH DE MI COMPU??
	string pacientFile = "Pacientes.csv";
	string contactFile = "Contactos.csv";
	string appointmentFile = "Consultas.csv";

	contacto contactPacient;
	int insuranceListSize = 0;
	string* insuranceList = new string[0];//en la funcion se le asigna una nueva direccion

	consulta appointment; //variable parac crear en struct de consulta
	appointment* appNewList = new appointment[0];
	appointment* appList = new appointment[0];

	int appointmentNewListSize = 0;
	int appSize = 0;
	bool medicalInsuranceArray = (pacientFile, &insuranceList, &insuranceListSize);
	readAppointment(appointmentFile, &appSize, appList);

	int a = 0;

	for (int k = 0; k < sizeFile; k++)
	{
		findContact(contactFile, &contactPacient, finalList[k].dniSecL);
		Busqueda(Pac * &l_Pacientes, int* tamactual, int dni);

		if(&l_Pacientes != nullptr)
		//hago todo siempre y cuando lo haya encontrado
		{
			for (a = 0; a < 10; a++) //llamo como maximo 10 veces cada paciente
			{
				answered = rand() % 2; //0: no contesto, 1: contesto
				if (answered == 1)
				{
					comeBack = rand() % 2;//0: no quiere volver, 1: quiere volver
					if (comeBack == 1)
					{
						generateApp(appNewList, &appointmentNewListSize, finalList[k].dniSecL, appSize, appList);
						finalList[k].answerSecL = "El paciente ha programado una nueva consulta";

						change = rand() % 2;//0: no quiere cambiar ningun dato 1:cambio su obra social
						if (change == 1)
						{
							if (medicalInsuranceArray)
							{
								string aux = finalList[k].medicalInsuranceSecL; //para que no sea la misma q tenia antes
								do
								{
									idInsurance = rand() % insuranceListSize;
									finalList[k].medicalInsuranceSecL = insuranceList[idInsurance];

								} while (aux == insuranceList[idInsurance]);
							}
						}
					}
					else //no quiere volver
					{
						finalList[k].answerSecL = "El paciente no desea volver";
					}
					break;
				}
			}
			if (a == 10) //si recorri el for entero entonces no contesto
				finalList[k].answerSecL = "El paciente no pudo ser contactado";
		}
	}

	fp.open(SecretaryFileName, ios::out); //abro archivo de la secretaria para sobreescribir
	if (!(fp.is_open()))
		return;
	fp << "DNI, Nombre, Apellido, Telefono, ObraSocial, ID-Medico, Estado" << endl;

	for (int i = 0; i < sizeFile; i++)
	{
		fp << finalList[i].dniSecL << " , " << finalList[i].namePacientSecL << " , " << finalList[i].lastNamePacientSecL << " , " << finalList[i].cellphoneNumberSecL << " , " << finalList[i].medicalInsuranceSecL << " , " << finalList[i].idDoctorSecL << " , " << finalList[i].answerSecL << endl;
	}
	fp.close();

	fp.open(appointmentFile, ios::app); //agrego las nuevas consultas al archivo original
	if (!(fp.is_open()))
		return;
	for (int j = 0; j < appointmentNewListSize; j++)
	{
		fp << appNewList[j].dniPacient << " , " << appNewList[j].dateRequest << " , " << appNewList[j].dateAppointment << " , " << appNewList[j].asistance << " , " << appNewList[j].idDoctor << endl;
	}
	fp.close();

	delete[] finalList;
	finalList = NULL;
	delete[] insuranceList;
	insuranceList = NULL;
	delete[] appNewList;
	appNewList = NULL;
	delete[] appList;
	appList = NULL;
}

//funcion busqueda
int keepingUpWithThePacients(Pac aux, int sizeListAppointment, appointment* listAppointment)
{
	int category = -1;
	appointment app;
	bool went;

	if (aux.state != "internado" && aux.state != "Internado" && aux.state != "fallecido" && aux.state != "Fallecido")
	{
		time_t current = time(0);
		time_t lastAp = lastAppointment(aux.dni, sizeListAppointment, listAppointment, &app);
		went = app.asistance;
		double timeSinceLastApp = difftime(current, lastAp);
		if (timeSinceLastApp < 315576000)//menos de 10 años en segundos
		{
			if (timeSinceLastApp > 0) // ya pasó
			{
				if (went)
					category = 3; //hace menos de 10 años, ya pasó su fecha y vino --> no me importa
				else
				category = 1;// hace menos de 10 años, ya pasó la fecha de la consulta y no vino --> recuperable
			}
			else
				category = 3; // hace menos de 10 años pero la consulta está programada para el futuro
		}
		else //hace más de 10 anos
		{
			if (!went)
				category = 2;// hace más de 10 años y no vino --> irrecuperable
			else
				category = 3;// hace más de 10 años pero vino --> no me importa
		}
	}
	else
	{
		if (aux.state == "internado" || aux.state == "Internado")
			category = 3; //está internado--> ya conozco su estado --> no me importa
		else //está muerto
			if (aux.state == "fallecido" || aux.state == "Fallecido")
			{
				category = 2; //muerto --> irrecuperable
			}
			else
				category = 3; //no conozco su estado --> no me importa
	}
	return category;
}

//grupo 14

bool chequearfechas(ultConsulta Consulta)
{
	time_t auxiliar_fecha = time(0);
	tm* hoy = localtime(&auxiliar_fecha);
	tm fecha_hoy;
	fecha_hoy.tm_mday = hoy->tm_mday;
	fecha_hoy.tm_mon = hoy->tm_mon;
	fecha_hoy.tm_year = hoy->tm_year;
	int dif = 0;//

	time_t aux_fin = mktime(&fecha_hoy);
	time_t aux_inicio = mktime(&(Consulta.consulta.fecha));
	dif = difftime(aux_fin, aux_inicio) / (31536000); //calculo la diferencia de tiempo en segundos y lo transformamos a anios

	if (dif > 10)
		return false;//no puede volver
	else
		return true; //puede volver
}

//idea para funBUSQUEDA ||aux1.dni = "404";//not found
bool informarsecretaria(Paciente pac, fstream& Archivados, fstream& Archivocontactos, fstream& archivopacientes)
{
	int n = 0;

	Contacto* contactoaux = new Contacto[n];
	Contacto contact;
	string aux;

	string encabezado;
	Paciente auxx;
	char coma = ',';
	int i = 0;
	int falso = -1;
	bool hola = vincularcontacto(pac, Archivocontactos); //funciona, puedo hacerlo por izquierda,falta vincular cont

	if (hola == true)
	{
		cout << "Llamando al paciente: " << pac.nombre << pac.apellido << "Su numero es: " << contact.celular << endl;
		cout << "Vuelve";
		cin >> aux;

		if (aux == "si" || aux == "Si" || aux == "SI" || aux == "sI")
		{
			cout << "Vuelve el paciente";
			pac.retorno = true;
			cout << "ingrese su nueva obra social";
			if (pac.obra_social != aux)
			{
				pac.obra_social = aux;
			}
			guardararchivo(archivopacientes, pac);
			return true;
		}
		else
		{
			cout << "No vuelve el paciente";
			pac.archivado = "archivado";
			guardararchivo(Archivados, pac);
			return false;
		}
	}
	else
		return false;
}
*/