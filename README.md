####Hópur 47
Verkefni 2


######DATA LAYER
- DONE: (*Arnar, Eiríkur*) Class for computer scientists [input checks, get functions and set functions by *Hrafnkell*] [seems to hold up]
- TODO(WIP): add sql-specific searching functions[current amount vector usage almost defeats the purpose of a SQL DB]
- DONE: (*Hrafnkell*) write/read settings to/from xml file [might need more settings depending on assignment]
- TODO(WIP): (*Hrafnkell*) smarter method to add to sql db [current style still has some leftovers from previous xml-implementation]

######DOMAIN LAYER
- TODO: Add person to database [current update() style needs to be replaced by some kind of add() function]
- DONE: (*Hrafnkell*) Processing settings requests [this still holds up, since settings are still stored in xml, might need more settings depending on assignment]
- DONE( * ): (*Arnar*) Sorting functions for correct ordering. [small work on using sort() by *Hrafnkell*] *This might need to be replaced by something more sql-y
- DONE( * ): (*Eiríkur*) Viewing only people of a certain gender [turned into private functions by *Hrafnkell*, but the code itself was written by *Eiríkur*] *Might need to be replaced
- TODO: Search [more sql-y style]

######PRESENTATION LAYER/UI(DONE(*))
- DONE: (*Arnar, Eiríkur, Hrafnkell*) Add new computer scientist from console
- DONE: (*Hrafnkell*) Main menu
- DONE: (*Hrafnkell*) Settings menu
- DONE: (*Hrafnkell*) Search from console.
- DONE: (*Hrafnkell*) display list from console.

*request.update() will have to be replaced here.. the rest will probably hold up

######FINISHED PRODUCT
- TODO: compile and add populated data.db and settings.xml to .zip/.rar
- TODO: turn the finished assignment in :)