## what do i need to modify
* something something
* [their collaboration note](https://hackmd.io/@coherent17/Hk1CdKACa#Taskflow-Simple-Usage-amp-Install)
## the todo list:
(their procedure seems stable, i.e. every execution generates same result.)
### Basic ideas
- [ ] modify optimization scheme
- [ ] modify placement scheme
- [ ] modify routing scheme
- [ ] a more precise timing module and wire length estimator
### Things that can be done:
- [ ] The cost function is different (no density constraint in cost.)
- [ ] mainly modify `Manager::preprocess()`, `Manager::banking()`, `Manager::postBankingOptimize()`,`Manager::detailplacement()`, `Manager::GetOverallCost()` and something it used
- [ ] `Manager::libscoring()`, i've heard that they only choose "some" cell to place, maybe we should use all?
- [ ] Timing model. originally use a weird model, now we can use FLUTE (`j29.pdf`, where to locate it?) to generate steiner points
- [ ] use a analytical approach to find the proper estimated length (`an.pdf`, `Gradient` class and its constructor parameters: what is being feeded into the class?)
- [ ] originally: if no where to place, don't merge -> can change to "Move to adjacent bins"
- [ ] examine `Preprocess::run()` & `Preprocess::optimalFFlocation()`
- [ ] examine `postBankingOptimizer::run()`
- [ ] enlarge the choosing window size to enable more merging
- [ ] ~~maybe we can slightly adjust the position of the combs~~
### report requirements
- [ ] a block/ flow diagram
- [ ] introduction of each test case
- [ ] test result arrange in a table (no screenshot!)
- [ ] reference list
- [ ] a screenshot of the registration.
- can just reference how the data are arranged in a proper paper.
### 
- **DO NOT MODIFY THE LEGALIZER, OR THE SOLUTION MIGHT BE ILLEGAL!**