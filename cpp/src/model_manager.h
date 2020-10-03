//
// Created by 刘也宽 on 2020/5/16.
//

#ifndef ALPHAZERO_RENJU_MODEL_MANAGER_H
#define ALPHAZERO_RENJU_MODEL_MANAGER_H

#include "cpp/src/model.h"
#include "cpp/src/resource_manager.h"
#include "cpp/src/data_structure/data_structure.h"
#include "absl/synchronization/mutex.h"

class ModelManager {
private:
    absl::Mutex train_model_mutex;
    absl::Mutex predict_model_mutex;
    Model train_model;
    Model predict_model;
public:
    static ModelManager& instance();

    void init();

    void train_on_batch(std::vector<Instance> instances) {}

    std::tuple<float, std::vector<float>> predict(FEATURE feature,  MODEL_TYPE model_type);

    void reset_train_model();

    void update_predict_model();
};


#endif //ALPHAZERO_RENJU_MODEL_MANAGER_H
