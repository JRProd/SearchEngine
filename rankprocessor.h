//rankprocess.h

#ifndef RANKPROCESSOR_H
#define RANKPROCESSOR_H

#include "page.h"
#include "query.h"
#include <vector>
#include <sstream>
#include <iterator>
#include <math.h>
#include <algorithm>

class RankProcessor {
public:
	RankProcessor();
    void getRank(Query query,std::vector<Page>& pages, int totalPages);
};
#endif
