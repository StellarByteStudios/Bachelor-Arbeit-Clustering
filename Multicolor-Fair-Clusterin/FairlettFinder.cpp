#include "FairlettFinder.h"

using namespace fairlettFinder;


// * * * =========== Using the Algorithm =========== * * * //
FairFlowReturnValues makeFairFlowClustering(vector<ColoredPoint> *, int)
{
    return FairFlowReturnValues();
}

FairFlowReturnValues *fairlettFinder::createGonzalezReturns(vector<ColoredPoint> *)
{
    return nullptr;
}

void fairlettFinder::deleteFairFlowReturns(FairFlowReturnValues *)
{
}





// * * * =========== Building the Graph and let it Flow =========== * * * //

void fairlettFinder::addNodesToGraph(Graph &, GraphData &)
{
}

void fairlettFinder::addArcsToGraph(Graph &, GraphData &, double)
{
}

void fairlettFinder::addCapacitiesToGraph(CapacityMap &, GraphData &)
{
}

Flow *fairlettFinder::calculateFlow(Graph &, CapacityMap &, GraphData &)
{
    return nullptr;
}

int fairlettFinder::getFlowOfArc(Flow &, Arc)
{
    return 0;
}

double fairlettFinder::findPotentionalRadius(vector<ColoredPoint> *)
{
    return 0.0;
}






// * * * =========== Calculating the Fairlets =========== * * * //

void fairlettFinder::makeCritFeatureSmalestFirst(vector<ColoredPoint> *)
{
}

void fairlettFinder::markFairletts(vector<ColoredPoint> *)
{
}










// * * * =========== Clustering with Fairlets =========== * * * //
void fairlettFinder::clusterRedPoints(vector<ColoredPoint> *)
{
}

vector<ColoredPoint> *fairlettFinder::filterRedPoints(vector<ColoredPoint> *)
{
    return nullptr;
}

double fairlettFinder::calculateMaxRadius(vector<ColoredPoint> *)
{
    return 0.0;
}

void fairlettFinder::updateClusterOfBluePoints(vector<ColoredPoint> *)
{
}
