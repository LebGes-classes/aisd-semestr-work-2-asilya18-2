    #include <vector>
    #include <iostream>
    #include <utility> // для pair
    #include <queue>

    using namespace std;

    enum vertexes { A, B, C, D, E, vertexes_count }; // перечисление констант - буквенных вершин 

    const vector<vector<pair<vertexes, int>>> graph = // фиксированный граф (так как сonst)
    // каждое ребро представлено парой <куда ведет ребро, вес ребра>
    { {{B, 1}, {C, 4}}, // ребра из вершины A 
    {{A, 1}, {C, 2}, {D, 5}},  // из B
    {{A, 4}, {B, 2}, {D, 3} }, // из С
    {{B, 5}, {C, 3} } // из D
    };

    vector<vector<pair<vertexes, int>>> prima (vertexes start) {/* в качестве параметра нашей основной функции prim 
        передаем начальную произвольную вершину */

    vector <bool> included_vertexes (vertexes_count, false); // массив размера == количеству вершин , определяет , вошла ли вершина в остов

    priority_queue<pair<int, pair<vertexes, vertexes>>, vector<pair<int, pair<vertexes, vertexes>>>, greater<>> queue; 
    /* это приоритетная очередь , которая с помощью компаратора greater<> определяет приоритетность пар вершин
    по возрастанию веса связывающих их ребер и потом помещает их в так называемый контейнер */

    vector<vector<pair<vertexes, int>>> ostov (vertexes_count); // наш граф после применения алгоритма

    included_vertexes[start] = true; // сразу включили начальную вершину в остов 
    for (const auto& pairs : graph[start]) { // отбираем ребра с началом в вершине start
        queue.push({pairs.second, {start, pairs.first}}); // std::pair ; добавляем в queue ребра , выходящие из начальной вершины
    }

    while (!queue.empty()) {
        pair<int, pair<vertexes, vertexes>> topElem = queue.top(); // отбираем ребро с наименьшим весом (int)
        int weight = topElem.first; // вес ребра
        pair<vertexes, vertexes> pairs = topElem.second; // пара вершин 
        
        queue.pop(); // удаление найденного ребра c наименьшим весом и его пары вершин

        vertexes u = pairs.first; // начальная вершина
        vertexes v = pairs.second; // конечная вершина 
        // соединенные ребром weight

        if (included_vertexes[v]) {
            continue; // если конечная вершина уже есть в остове , переходим к началу цикла
        }

        included_vertexes[v] = true;
        ostov[u].push_back({v, weight}); // добавляем ребро u - v (v - u)
        ostov[v].push_back({u, weight});

        for (const auto& pairs : graph[v]) { 
             if (!included_vertexes[pairs.first]) {
                 queue.push({pairs.second, {v, pairs.first}});
             }
        }
    }

    return ostov;  
}

int main() {

     auto result = prima(C);

    cout << "{\n";
    for (int i = 0; i < vertexes_count; ++i) {
        cout << "    {";
        for (size_t j = 0; j < result[i].size(); ++j) {
            cout << " {" << char('A' + result[i][j].first) << ", " << result[i][j].second << "}";
            if (j < result[i].size() - 1) {
                cout << ",";
            }
        }
        cout << " }"; 
        if (i < vertexes_count - 1) {
            cout << ","; 
        }
        cout << " // ребра из вершины " << char('A' + i) << "\n"; // добавляем комментарии о начальной вершине 
    }
    cout << "};\n";

     return 0;
}

