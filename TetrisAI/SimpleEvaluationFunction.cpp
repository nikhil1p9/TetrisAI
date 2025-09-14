
#include "SimpleEvaluationFunction.h"


float SimpleEvaluationFunction::number_of_holes(Board board) {

    int changes = 0;
    for(int j=1; j < board.get_width(); j++) {
        int found_block = -1;
        for (int i = 0; i < board.get_height(); i++) {
            if (board.is_filled(j,i) && found_block < 0) {
                found_block = i;
            }
            else {
                if (found_block != -1) {
                    changes += abs(found_block - i);
                }
            }
        }
	}
    return changes;
}

float SimpleEvaluationFunction::aggregate_height(Board board)
{
    int aggregate_height = 0;
    for (int j = 0; j < board.get_width(); j++) {
        for (int i = 0; i < board.get_height(); i++) {
            if (board.is_filled(j,i)) {
                aggregate_height += (board.get_height() - i);
                break;
            }
        }
    }
    return aggregate_height;
}

float SimpleEvaluationFunction::variance_of_heights(Board board)
{
	std::vector<int> heights(board.get_width(), 0);
	int avg_height = 0;
    for(int j = 0; j < board.get_width(); j++) {
        for (int i = 0; i < board.get_height(); i++) {
            if (board.is_filled(j,i)) {
				heights[j] = board.get_height() - i;
				avg_height += heights[j];
                break;
            }
        }
	}
	avg_height /= board.get_height();
	int variance = 0;
    for (int h : heights) {
        variance += (h - avg_height) * (h - avg_height);
	}
	variance /= board.get_width();
    return variance ;

}

float SimpleEvaluationFunction::no_of_lines_deleted(Board board)
{
    int cnt = 0;
    for(int i=0;i< board.get_height(); ++i) {
        cnt += board.copy().delete_lines();
        
	}
    return cnt;
}

float SimpleEvaluationFunction::is_last_column_empty(Board board)
{
    for(int i = 0; i < board.get_height(); ++i) {
        if(board.is_filled(board.get_width()-1,i)) return 0.0f;
	}
    return 1.0f;
}
