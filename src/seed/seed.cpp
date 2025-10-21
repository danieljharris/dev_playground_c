#include "seed.h"

Seed::Seed() {
    vector<int> seeds;
    mapOmaps metaMaps;

    tie(seeds, metaMaps) = ingest();

    spdlog::info("Starting search...");
    for (int seed : seeds) {
        int currentValue = seed;
        spdlog::debug("Seed search: {}", currentValue);
        for (maps mapList : metaMaps) {
            for (map singleMap : mapList) {

                spdlog::debug("  looking at {} {} {}", singleMap.source, singleMap.dest, singleMap.length);

                if (currentValue >= singleMap.source && currentValue <= (singleMap.source + singleMap.length)) {

                    int newValue = (currentValue - singleMap.source) + (singleMap.dest);
                    spdlog::debug("      moving from {} to {} as it hit: {} {} {}",
                        currentValue, newValue, singleMap.source, singleMap.dest, singleMap.length);
                    currentValue = newValue;

                    break;
                }
            }
        }

        spdlog::info("seed {} maps to location {}", seed, currentValue);
    }
    spdlog::info("Search Finished!");
}

bool isWhitespace(string text) {
    return text.empty() || text == "" || text == " " || text == "\n" || text == "\r";
}

optional<maps> getNextMaps(ifstream &sampleData) {
    string text;

    //Clear title (not needed), return if empty (EOF)
    if(!getline(sampleData, text)) return nullopt;

    maps newMaps;
    while (getline(sampleData, text)) {
        vector<int> numbers;
        if (isWhitespace(text)) break;

        stringstream line(text);
        string lineText;

        while (getline(line, lineText, ' ')) {
            numbers.push_back(stoi(lineText));
        }

        newMaps.push_back(map(numbers[1], numbers[0], numbers[2]));
    }

    return newMaps;
}

tuple<vector<int>, mapOmaps> Seed::ingest() {
    ifstream sampleData("/workspaces/dev_playground_c/src/seed/data/sample_data.txt");

    vector<int> seeds;
    mapOmaps metaMaps;

    // Skip "seeds:"
    string text;
    getline(sampleData, text);

    spdlog::info("Here: 1");

    while (getline(sampleData, text)) {
        if (isWhitespace(text)) break;

        stringstream line(text);
        string lineText;
        while (getline(line, lineText, ' ')) {
            seeds.push_back(stoi(lineText));
        }
    }

    spdlog::info("Here: 2");

    bool linesRemaining = true;
    do {
        optional<maps> result = getNextMaps(sampleData);
        if (result) metaMaps.push_back(*result);
        else linesRemaining = false;
    } while (linesRemaining);

    spdlog::info("Here: 3");

    sampleData.close();

    return make_tuple(seeds, metaMaps);
}