#include "movie.h"

Movie** create_movies(void)
{
    Movie movies[SIZE_DATA]=
            {
                    {1,"Blade Runner 2049\0",2017,80},
                    {2,"Interstellar\0",2014,87},
                    {3,"Mad Max: Fury Road\0",2015,81},
                    {4,"Children of Men\0",2006,79},
                    {5,"Inception\0",2010,88},
                    {6,"Tenet\0",2020,73},
                    {7,"Once Upon a Time... In Hollywood\0",2019,76},
                    {8,"Inglourious Basterds\0",2009,84},
                    {9,"The Lord of the Rings: The Return of the King\0",2003,90},
                    {10,"The Wolf of Wall Street\0",2013,82},
                    {11,"Disturbia\0",2007,68},
                    {12,"Dunkirk\0",2017,78},
                    {13,"Troy\0",2004,73},
                    {14,"The Dark Knight\0",2008,90},
                    {15,"Forrest Gump\0",1994,88},
                    {16,"Fight Club\0",1999,88},
                    {17,"Star Wars: Episode V - Empire Strikes Back\0",1980,87},
                    {18,"The Silence of the Lamps\0",1991,86},
                    {19,"Saving Private Ryan\0",1998,86},
                    {20,"The Departed\0",2006,85},
                    {21,"Whiplash\0",2014,85},
                    {22,"Spider-Man: Into the Spider-Verse\0",2018,85},
                    {23,"Avengers: Infinity War\0",2018,84},
                    {24,"Django Unchained\0",2012,85},
                    {25,"The Ministry of Ungentlemanly Warfare\0",2024,73},
                    {26,"Godzilla x Kong: The New Empire\0",2024,65},
                    {27,"Monkey Man\0",2024,71},
                    {28,"Road House\0",2024,62},
                    {29,"Rebel Moon - Part Two: The Scargiver\0",2024,52},
                    {30,"Wish\0",2023,56},
                    {31,"Anyone But You\0",2023,62},
                    {32,"The Fall Guy\0",2024,74},
                    {33,"The Bricklayer\0",2023,51},
                    {34,"Anatomy of a Fall\0",2023,77},
                    {35,"Hit man\0",2023,77},
                    {36,"Glass\0",2019,66},
                    {37,"Barbie\0",2023,68},
                    {38,"Stolen\0",2024,56},
                    {39,"Madame Web\0",2024,38},
                    {40,"Joker\0",2019,84},
                    {41,"The Shawshank Redemption\0",1994,93},
                    {42,"Pulp Fiction\0",1994,92},
                    {43,"Titanic\0",1997,89},
                    {44,"The Matrix\0",1999,87},
                    {45,"The Sixth Sense\0",1999,85},
                    {46,"Gladiator\0",2000,86},
                    {47,"Memento\0",2000,85},
                    {48,"The Lord of the Rings: The Fellowship of the Ring\0",2001,88},
                    {49,"A Beautiful Mind\0",2001,86},
                    {50,"Spirited Away\0",2001,89},
                    {51,"The Lord of the Rings: The Two Towers\0",2002,89},
                    {52,"Finding Nemo\0",2003,90},
                    {53,"The Incredibles\0",2004,89},
                    {54,"Eternal Sunshine of the Spotless Mind\0",2004,88},
                    {55,"Million Dollar Baby\0",2004,87},
                    {56,"Brokeback Mountain\0",2005,87},
                    {57,"Crash\0",2004,78},
                    {58,"Pan's Labyrinth\0",2006,89},
                    {59,"The Prestige\0",2006,88},
                    {60,"No Country for Old Men\0",2007,90},
                    {61,"There Will Be Blood\0",2007,89},
                    {62,"WALL-E\0",2008,89},
                    {63,"Slumdog Millionaire\0",2008,88},
                    {64,"The Dark Knight\0",2008,90},
                    {65,"Up\0",2009,88},
                    {66,"Avatar\0",2009,83},
                    {67,"Inception\0",2010,88},
                    {68,"Toy Story 3\0",2010,87},
                    {69,"Black Swan\0",2010,85},
                    {70,"The Social Network\0",2010,88},
                    {71,"The King's Speech\0",2010,87},
                    {72,"The Artist\0",2011,88},
                    {73,"Hugo\0",2011,87},
                    {74,"The Help\0",2011,81},
                    {75,"The Avengers\0",2012,85},
                    {76,"Django Unchained\0",2012,87},
                    {77,"Life of Pi\0",2012,86},
                    {78,"Gravity\0",2013,87},
                    {79,"12 Years a Slave\0",2013,88},
                    {80,"Her\0",2013,89},
                    {81,"Boyhood\0",2014,87},
                    {82,"Birdman or (The Unexpected Virtue of Ignorance)\0",2014,88},
                    {83,"The Grand Budapest Hotel\0",2014,87},
                    {84,"Spotlight\0",2015,88},
                    {85,"Mad Max: Fury Road\0",2015,90},
                    {86,"The Revenant\0",2015,88},
                    {87,"La La Land\0",2016,89},
                    {88,"Arrival\0",2016,88},
                    {89,"Moonlight\0",2016,88},
                    {90,"Get Out\0",2017,87},
                    {91,"Dunkirk\0",2017,89},
                    {92,"The Shape of Water\0",2017,87},
                    {93,"Three Billboards Outside Ebbing, Missouri\0",2017,88},
                    {94,"Coco\0",2017,89},
                    {95,"Call Me by Your Name\0",2017,88},
                    {96,"Lady Bird\0",2017,87},
                    {97,"Bohemian Rhapsody\0",2018,88},
                    {98,"A Star is Born\0",2018,87},
                    {99,"Black Panther\0",2018,88},
                    {100,"Parasite\0",2019,89},
                    {101,"Jojo Rabbit\0",2019,87},
                    {102,"Joker\0",2019,86},
                    {103,"Once Upon a Time... In Hollywood\0",2019,88},
                    {104,"1917\0",2019,88},
                    {105,"The Irishman\0",2019,87}
            };

    Movie **Pmovies = (Movie**)calloc(SIZE_DATA,sizeof(Movie*));
    int i;
    for(i=0;i<SIZE_DATA;i++)
    {
        Pmovies[i] = (Movie*)calloc(1,sizeof(Movie));
        *(Pmovies[i]) = movies[i];
    }
    return Pmovies;
}



Movie* getMovie(Movie **movies,int index)
{
    if(index >= 0 && index <= (SIZE_DATA-1))
        return movies[index];
    else
        return NULL;

}

void printMovie(Movie *movie)
{
    printf("%-3d | %-50s | %d | %d ",movie->id, movie->name,movie->release_date,movie->rating);
    printf("\n");
    //printf("%-2d | %-48s | %d | %d",pelicula->id,pelicula->nombre,pelicula->fecha,pelicula->calificacion);
}