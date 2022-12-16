//
// Created by 이은서 on 2022/10/04.
//

#ifndef PROJECT1_RESULT_H
#define PROJECT1_RESULT_H

enum Result
{
    Success = 0,

    CommandFileNotExist = 100,
    LoadFileNotExist, // 101

    LoadedListNotExist = 200,
    AddFileNotExist,
    ParameterLack,

    ModifyError = 300,
    UniqueNumExist,

    MoveError = 400,

    PrintError = 500,

    SearchError = 600,

    SelectError = 700,

    EditError = 800,
	EditFileLoadError,
	

    WrongCommandImput = 777,
};

#endif //PROJECT1_RESULT_H
