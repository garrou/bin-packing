/**
 * @file Heuristic.cpp
 * @author Adrien GARROUSTE - 1irda.alwaysdata.net
 * @brief Class to launch heuristic method 
 * @version 0.1
 * @date 2021-01-04
 * @copyright No copyright no right
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "../headers/Heuristic.hpp"
#include "../headers/Box.hpp"
#include "../headers/Item.hpp"

/**
 * @brief Construct a new object
 * @param algorithm algorithm choosed by user
 * @param box_size size of all boxes
 * @param values_size all size of values to put in boxes
 */
Heuristic::Heuristic(int algorithm, int box_size, std::vector<int> values_size) {

    this->algorithm = algorithm;
    this->box_size = box_size;
    this->nb_taken = 0;

    for (int size : values_size) {
        this->items_container.push_back(Item(size));    
    }
}

/**
 * @brief First fit algorithm
 */
void Heuristic::first_fit() {

    int current_box = 0;

    while (this->nb_taken != this->items_container.size()){

        this->boxes_container.push_back(Box(this->box_size));

        for (size_t current_item = 0; current_item < this->items_container.size() 
            && this->boxes_container[current_box].get_capacity() > 0; current_item++) {

            if (this->items_container[current_item].get_size() <= this->boxes_container[current_box].get_capacity()
                && !this->items_container[current_item].get_is_taken()) {

                this->boxes_container[current_box].put(this->items_container[current_item]);
                this->nb_taken++;
            }
        }

        current_box++;
    }
}

/**
 * @brief Best fit algorithm
 */
void Heuristic::best_fit() {
}

/**
 * @brief Sort vector in descending order
 */
void Heuristic::descending_order() {
    std::sort(this->items_container.begin(), 
            this->items_container.end(), 
            [](const Item &a, const Item &b) -> bool { return a.get_size() > b.get_size(); });
}

/**
 * @brief Display results
 */
void Heuristic::display() {

    std::cout << "Number of boxes used : " << this->boxes_container.size() << std::endl;

    for (size_t i = 0; i < this->boxes_container.size(); i++) {
        std::cout << "Box n°" << i + 1 << " : ";
        this->boxes_container[i].display_content();
    }
}

/**
 * @brief Choose algo to launch
 */
void Heuristic::choose_algo() {

    switch (this->algorithm) 
    {
        case 1: 
        {
            this->first_fit();
            break;
        }
        
        case 2: 
        {
            this->descending_order();
            this->first_fit();
            break;
        }

        case 3: 
        {
            this->best_fit();
            break;
        }

        case 4: 
        {
            this->best_fit();
            this->first_fit();
            break;
        }
    }
}

/**
 * @brief Launch heuristic method
 */
void Heuristic::launch() {
    this->choose_algo();
    this->display();
}