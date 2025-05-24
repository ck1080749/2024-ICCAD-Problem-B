#include "PostBankingOptimizer.h"
#include "OptimalLocation.h"

postBankingOptimizer::postBankingOptimizer(Manager &mgr) : mgr(mgr)
{
}

postBankingOptimizer::~postBankingOptimizer()
{
}

void postBankingOptimizer::run()
{
#ifndef NDEBUG
    std::cout << "[Post banking optimize]" << std::endl;
#endif
    // create FF logic
    std::unordered_map<std::string, int> idx_map;
    std::vector<FF *> FFsFixed;
    std::vector<FF *> FFs(mgr.FF_Map.size());
    FFsFixed.reserve(mgr.FF_Map.size());
    size_t i = 0;

    for (auto &FF_m : mgr.FF_Map)
    {
        FF *curFF = FF_m.second;
        // if(1 || !curFF->getFixed()){ // ignore fixed idea, it does improve :(
        if (!curFF->getIsLegalize())
        {
            FFsFixed.push_back(curFF);
        }
        FFs[i] = curFF;
        i++;
    }

    vector<Coor> oldCoor(FFsFixed.size());
    for (size_t j = 0; j < FFsFixed.size(); j++)
        oldCoor[j] = FFsFixed[j]->getNewCoor();
    postBankingObjFunction obj(mgr, mgr.FF_Map, idx_map, FFsFixed.size(), FFsFixed);
    const double kAlpha = mgr.Bit_FF_Map[1][0]->getW();
    Gradient optimizer(mgr, mgr.FF_Map, obj, kAlpha, idx_map, FFsFixed.size(), FFsFixed);

#ifndef NDEBUG
    std::cout << "Slack statistic before Optimize" << std::endl;
    std::cout << "\tTNS : " << mgr.getTNS() << std::endl;
#endif
    double prevTNS = mgr.getTNS();
    const double terminateThreshold = 0.001;
    for (i = 0; i <= 1000; i++)
    {
        optimizer.Step(true);

        // update original data
        if (i % 25 == 0)
        {
#ifndef NDEBUG
            std::cout << "\nphase 1 step : " << i << std::endl;
            std::cout << "Slack statistic after Optimize" << std::endl;
            std::cout << "\tTNS : " << mgr.getTNS() << std::endl;
#endif
        }
        double newTNS = mgr.getTNS();
        if (abs(newTNS - prevTNS) / abs(prevTNS) < terminateThreshold || newTNS >= prevTNS)
        {
#ifndef NDEBUG
            std::cout << "\n\nGradient Convergen at " << i << " iteration." << std::endl;
            std::cout << "Final statistic" << std::endl;
            std::cout << "\tTNS : " << mgr.getTNS() << std::endl;
#endif
            if (newTNS > prevTNS && i == 0)
                for (size_t j = 0; j < FFsFixed.size(); j++)
                {
                    FFsFixed[j]->setNewCoor(oldCoor[j]);
                    FFsFixed[j]->setCoor(oldCoor[j]);
                }
            break;
        }
        prevTNS = newTNS;
    }
}

void postBankingOptimizer::changeCell()
{
    // size_t bitMapSize = mgr.Bit_FF_Map[1].size();
    // vector<FF *> FFs(FF_list.size());
    // size_t FFidx = 0;
    // for (auto &ff_m : FF_list)
    // {
    //     FFs[FFidx] = ff_m.second;
    //     FFidx++;
    // }
    // // bool forceSmaller = mgr.alpha / (mgr.alpha + mgr.beta + mgr.gamma) > 0.1;
    // // debank and save all the FF in logic_FF;
    // // which is all one bit ff without technology mapping(no cell library)
    // for (size_t i = 0; i < FFs.size(); i++)
    // {
    //     FF *curFF = FFs[i];
    //     double bestCost = 0;
    //     Cell *bestCell = curFF->getCell();

    //     // iterate through all single bit cell type
    //     for (size_t j = 0; j < bitMapSize; j++)
    //     {
    //         Cell *targetCell = mgr.Bit_FF_Map[1][j];
    //         double TimingCost = 0;
    //         Cell *curCell = curFF->getCell();
    //         // delta q pin delay will propagate to all fanout endpoints
    //         TimingCost += (targetCell->getQpinDelay() - curCell->getQpinDelay()) * curFF->getNextStage().size();
    //         TimingCost += mgr.DisplacementDelay * (HPWL(curFF->getCoor() + curFF->getPinCoor("D"), curFF->getCoor() + targetCell->getPinCoor("D")) + HPWL(curFF->getCoor() + curFF->getPinCoor("Q"), curFF->getCoor() + targetCell->getPinCoor("Q")) * curFF->getNextStage().size());
    //         double AreaCost = targetCell->getArea() - curCell->getArea();
    //         double PowerCost = targetCell->getGatePower() - curCell->getGatePower();
    //         double totalCost = mgr.alpha * TimingCost + mgr.beta * PowerCost + mgr.gamma * AreaCost;
    //         // hard constraint for using smaller cell, for easier legalize, need reconsider
    //         if (totalCost < bestCost)
    //         { // && ((targetCell->getW() <= curCell->getW() && targetCell->getH() <= curCell->getH()) || !forceSmaller)){
    //             bestCost = totalCost;
    //             bestCell = targetCell;
    //         }
    //     }
    //     if (bestCost != 0)
    //     {
    //         changed = true;
    //         curFF->setCell(bestCell);
    //         curFF->setFixed(false);
    //     }
    // }

    // // update slack and change origialQpinDelay
    // updateSlack(FFs);
    // for (size_t i = 0; i < FFs.size(); i++)
    // {
    //     FF *curFF = FFs[i];
    //     curFF->setOriginalQpinDelay(curFF->getCell()->getQpinDelay());
    // }
}
