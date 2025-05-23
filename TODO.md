## what do i need to modify
* something something
* [their collaboration note](https://hackmd.io/@coherent17/Hk1CdKACa#Taskflow-Simple-Usage-amp-Install)
## the todo list:
(their procedure seems stable, i.e. every execution generates same result.)
### Basic ideas
- [ ] modify optimization scheme
- [x] ~~modify placement scheme~~
- [x] ~~modify routing scheme~~
- [x] ~~a more precise timing module and wire length estimator -> hard to modify under current structure.~~
### Things that can be done:
- [x] ~~The cost function is different (no density constraint in cost.)~~
- [ ] mainly modify `Manager::preprocess()`, `Manager::banking()`, `Manager::postBankingOptimize()`,`Manager::detailplacement()` and something it used
  - [x] `Manager::preprocess()`: nothing can be modified quickly
  - [ ] `Manager::banking()`
  - [ ] `Manager::postBankingOptimize()`
  - [ ] `Manager::detailplacement()` -> prbably sholdn't do this
- [x] ~~Timing model. originally use a weird model, now we can use FLUTE (`j29.pdf`, where to locate it?) to generate steiner points~~
- [x] ~~use a analytical approach to find the proper estimated length (`an.pdf`, `Gradient` class and its constructor parameters: what is being feeded into the class?)~~
  - The HPWL measured in the `Preprocess::updateSlack()` is basically impossible to modify. but since it only includes two node (prev gate and current gate), there should not be a problem though.
  - harder to do under current scheme.
- [x] ~~maybe we can slightly adjust the position of the combs~~

### final thoughts
- [x] **choose a "best suiting cell" during `void Banking::doClustering()`, and further optimize in `postBankingOptimizer::run()`**
  - the other ff with lower score doesn't seems to produce better results though... maybe scoring is really good?
  - changed to "move to an inferior cell if cannot find somewhere to place" -> doesn't seems to have sig result too.
- [ ] originally: if no where to place, don't merge -> can change to "Move to adjacent bins" (in `Legalizer::FindPlace()`)
- [ ] examine the difference `postBankingOptimizer::run()` `Preprocess::optimalFFlocation()`
- [ ] enlarge the choosing window size to enable more merging -> no presence of windows, how to modify?
- [x] in `Banking::chooseCandidateFF(...)`: maybe try more combination? (1+2 cannot, 2+3 cannot; but can 1+3 condition) -> probably wont be better though.
### report requirements
- [ ] a block/ flow diagram
- [ ] introduction of each test case
- [ ] test result arrange in a table (no screenshot!)
- [ ] reference list
- [ ] a screenshot of the registration.
- can just reference how the data are arranged in a proper paper.
### 
- **DO NOT MODIFY THE LEGALIZER, OR THE SOLUTION MIGHT BE ILLEGAL!**
  
## analysis
### preprocess
* optimal ff location: optimizer runs 1000 times
* class gradient: just deal with gradient step. the important part should be the object fucntion.
* `Preprocess::ChangeCell()`: change the cell type to the one with smalles cost under current coindition.
  * this is doing without consider the actual pos of each cell.
  * maybe use analytical cell size, along witb optimizer?
  * `TimingCost += (targetCell->getQpinDelay() - curCell->getQpinDelay()) * curFF->getNextStage().size();`
* 123

### banking
* they only choose the smallest cell as target -> which is fine if they will chang the cell later.
* banking choosing procedure:   
  1. choose ffs with same clock id
  2. select one of the ffs 
  3. find the neareast ffs and try to merge them
* we can try different ff cells when merging?
* `Banking::chooseCandidateFF(...)` examines some neareast nodes to check, but only selects some a smaller number of it (target bit) to merge
### post banking optimize
* only optimize position, maybe try to optimize cell selection as well

## done things:
* they choose the best single bit ff when legalize, 
