
MicroEvolution Sim 1.0                 7/29/13

by Zachary Horvitz

************************************************************************************************************************************************************************

This simulation models microevolution by placing an agent('&') in a randomly 
generated world, throughout which resources are scattered. The user can set the 
lifespan, energy, and food type of the organism. When the agent reaches an available. 
resource('$'), it reproduces, cloning itself with a probability of mutation, the 
magnitude of which is set by the user. The ability of the inherited traits to 
perform in the enviorment results in the overall success of the organism, 
therefore increased reproduction, therefore, fecundity. This, in theory, should 
result in demography. 

 
The resources of the initial world are set at a value of 5. For every unit the 
agent's food type is different than the resource's food, the unit does not replenish 2.
A more adapted agent will have a closer food type to the resource.


In any enviornment, there is change change. The user of this simulation inputs the interval 
at which enviornmental change occurs. Every change, the resources are changes by a random amount. 
This change can be thought of as an ice age, resulting in extinction, as certain members of the species
will be unable gain energy and reproduce.


Trait distributions are saved to the excel file titled: "&distribution.csv". From here, they can be graphed.
This information can be used to observe the nature of selection (i.e. directionality).

