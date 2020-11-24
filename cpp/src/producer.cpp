//
// Created by 刘也宽 on 2020/10/3.
//
#include "producer.h"
#include "cpp/src/strategy/mcts_strategy.h"

Producer::Producer(int thread_pool_size) : thread_pool_size(thread_pool_size){
    init_data_pool();
}

void Producer::play_a_game() {
    auto& conf = ResourceManager().get_conf();
    MctsStrategy stg1(conf.mtcs_conf());
    MctsStrategy stg2(conf.mtcs_conf());
    GameResult result = pit.play_a_game((Strategy*)&stg1, (Strategy*)&stg2);
    for(auto instance: game_result_to_instances(result)) {
        ResourceManager::instance().get_data_pool().push_back(instance);
    }
}

void Producer::play_endless() {
    while(true) {
        play_a_game();
    }
}

void Producer::init_data_pool() {
    FixedDeque<Instance>& pool = ResourceManager::instance().get_data_pool();
    ThreadPool thread_pool(thread_pool_size);
    std::vector<std::future<void>> futures;
    while(true) {
        for(size_t i = 0; i < thread_pool_size; i++) {
            futures.emplace_back(thread_pool.enqueue(&Producer::play_a_game, this));
        }
        for (auto&& future: futures) {
            future.get();
        }
        if (ResourceManager::instance().get_data_pool().full()) {
            std::cout << "init data pool done!" << std::endl;
            return;
        }
    }
}

void Producer::run() {
    ThreadPool thread_pool(thread_pool_size);
    std::vector<std::future<void>> futures;
    for(size_t i = 0; i < thread_pool_size; i++) {
        futures.emplace_back(thread_pool.enqueue(&Producer::play_endless, this));
    }
}

Producer::~Producer() {

}

void Producer::stop() {

}