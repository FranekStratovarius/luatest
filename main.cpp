#include <lua.hpp>

void printvalue(lua_State* L,int idx){
		if(lua_isnil(L,idx))
			printf("nil");
		else if(lua_isboolean(L,idx))
			printf("%s",lua_toboolean(L,idx)?"true":"false");
		else if(lua_isinteger(L,idx))
			printf("%d",(int)lua_tointeger(L,idx));
		else if(lua_isnumber(L,idx))
			printf("%f",lua_tonumber(L,idx));
		else if(lua_isstring(L,idx))
			printf("%s",lua_tostring(L,idx));
}

void printtable(lua_State* L,int depth=0){
	//den befehl hab ich nicht ganz geblickt, aber damit geht man auf dem stack in ne tabelle rein
	lua_pushnil(L);
	//solange es weitere werte in der tabelle gibt, wird sie durchlaufen
	while(lua_next(L,-2)!=0){
		//einrückung damits schön aussieht^^
		for(int i=0;i<depth;i++)printf("  ");
		//wenn tabelle in aktueller tabelle in diese absteigen
		if(lua_istable(L, -1)){
			//formatierung für schöne ausgabe
			//key ausgeben
			printvalue(L,-2);
			printf(":{\n");
			//in verschachtelte tabelle absteigen (und für die einrückung eins hochzählen)
			printtable(L,depth+1);
			for(int i=0;i<depth;i++)printf("  ");
			printf("},\n");
		//sonst key-value paare ausgeben
		}else{
			//key ausgeben
			printvalue(L,-2);
			printf("=");
			//value ausgeben
			printvalue(L,-1);
			printf(",\n");
		}
		//wenn wert bearbeitet von stack nehmen
		lua_pop(L,1);
	}
}

int main(){
	//lua laden
	lua_State* L=luaL_newstate();
	//standartlibraries von lua laden falls nötig
	//z.B.: os.etc math.etc string.etc etc...
	//wenn man sie nicht braucht kann man das auch weglassen
	luaL_openlibs(L);
	//luafile laden
	int result=luaL_loadfile(L,"table.lua");
	if(result==LUA_OK)
		//falls ok geladen luafile ausführen
		lua_pcall(L,0,LUA_MULTRET,0);
	else
		//fehlermeldung, danach sollte man ne fehlerbehandlung machen
		printf("Konnte Luascript nicht laden\n");

	//****************************
	//***rückgabewerte ausgeben***
	//****************************
	//in diesem beispiel wird der returnwert des scripts ausgegeben
	if(lua_istable(L,-1))
		printtable(L);

	//************************
	//***funktion ausführen***
	//************************
	//hier wird eine funktion ausgeführt die als globale variable angelegt wurde
	lua_getglobal(L,"sum");
	//erstes argument auf stack schieben
	lua_pushnumber(L,4);
	//zweites argument auf stack schieben
	lua_pushnumber(L,6);
	//funktion mi lua_State,2 übergabewerten und 1 rückgabewert aufrufen
	lua_call(L,2,1);
	//resultat von stack lesen
	printf("summe: %f\n",lua_tonumber(L,-1));
	//wert vom stack kicken
	lua_pop(L,-1);


	//luastate killen
	lua_close(L);
	return 0;
}
