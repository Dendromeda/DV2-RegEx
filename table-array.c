#include <stdlib.h>
#include <string.h>

#include "table.h"


//En struct för nyckel/värde-par
typedef struct{
	KEY key;
	VALUE val;
} cell;

//Nyckel/värdepar sparas i en array vars storlek är definierad av capacitet
struct table
{
	int cap;
	int size;
	cell *arr;
	key_compare_func key_cmp;
};

// ------  Custom code for DV2-OU2  ------

void table_sort(table *t){
	cell tmp;
	for (int i = t->size-1; i >= 0; i--){
		for (int j = 0; j < i; j++){
			int *v1 = t->arr[j].val;
			int *v2 = t->arr[j+1].val;
			if (*v1 < *v2){
				tmp = t->arr[j];
				t->arr[j] = t->arr[j+1];
				t->arr[j+1] = tmp;
			}
		}
	}
}


int table_getEntry(table *t, char *str, int idx){
	cell c = t->arr[idx];
	int *val = c.val;
	strcpy(str, c.key);
	return *val;
}


int table_getSize(table *t){
	return t->size;
}


// ------ End of custom code  ------


//Söker igenom tabellen och returnerar en pekare till rätt nyckel/värde-par. Returnrar NULL om nyckeln ej hittas
cell *table_search(table *t,KEY key){
	for (int i = 0; i < t->size; i++){
		cell *c = &(t->arr[i]);
		if (t->key_cmp(key, c->key) ){
			return c;
		}
	}
	return NULL;
}

// Frigör ett par c1 och lägger in paret c2 istället
void cell_replace(cell *c1, cell *c2){
	free(c1->key);
	free(c1->val);
	c1->key = c2->key;
	c1->val = c2->val;
}

table *table_empty(int capacity, key_compare_func cmp)
{
    table *t;
    t = malloc(sizeof *t);
	t->cap = capacity;
	t->size = 0;
    t->arr = malloc(capacity*sizeof(cell)); //Array med storlek capacity skapas och får allokerat minne
	t->key_cmp = cmp;
    return t;
}


bool table_is_empty(table *t)
{
    return t->size == 0;
}


void table_insert(table *t, KEY key, VALUE val)
{
	if (t->size >= t->cap){ // Specialiserad kod för DV2-OU2
		t->arr = realloc(t->arr, sizeof(cell)*(t->size + 5));
		t->cap = t->cap+5;
	}
	cell *c = table_search(t,key);
	if (c != NULL){ // Om det finns dublett
		free(c->key); //De gamla pekarna till nyckel och värde frigörs för att hindra minnesläcka
		free(c->val);
		c->key = key;
		c->val = val;
		return;
	}
	c = &(t->arr[t->size]); // Om det ej finns dublett läggs ett nytt n/v-par in längst bak i arrayen
	c->key = key;
	c->val = val;
	t->size += 1;

}


VALUE table_lookup(table *t, KEY key)
{
	cell *c = table_search(t,key);
	if (c == NULL){ // Om n/v-par ej hittas
		return NULL;
	}
	return c->val;
}


void table_remove(table *t, KEY key)
{
    cell *c = table_search(t,key);
	if (c == NULL){
		return;
	}
	t->size--;
	cell *c2 = &(t->arr[t->size]);//Byter ut n/v-paret som ska tas bort med det sista paret i tabellen,
	cell_replace(c, c2); //			eftersom size har minskats ligger det nu utanför tabellen
}


void table_kill(table *t)
{
	for (int i = 0; i < t->size; i++){  //Eftersom alla n/v-pekare utanför tabellen antingen har en dublett någonstans i tabellen,
		free(t->arr[i].key);			//eller pekar på en redan frigjord adress, behöver bara n/v-pekarna frigöras upp till arr[t->size]
		free(t->arr[i].val);
	}
    free(t->arr);
    free(t);
}
