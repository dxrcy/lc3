#include "assemble.cpp"
#include "cli.cpp"
#include "error.hpp"
#include "execute.cpp"

void try_run(Options &options);

int main(const int argc, const char *const *const argv) {
    Options options;
    parse_options(options, argc, argv);

    // TODO(feat): Print out different message for each error

    try_run(options);
    switch (ERROR) {
        case ERR_OK:
            break;
        default:
            printf("ERROR: 0x%04x\n", ERROR);
            return ERROR;
    }

    return ERR_OK;
}

void try_run(Options &options) {
    switch (options.mode) {
        case Mode::ASSEMBLE_ONLY:
            assemble(options.in_file, options.out_file);
            OK_OR_RETURN();
            break;

        case Mode::EXECUTE_ONLY:
            execute(options.in_file);
            OK_OR_RETURN();
            break;

        case Mode::ASSEMBLE_EXECUTE:
            assemble(options.in_file, options.out_file);
            OK_OR_RETURN();
            execute(options.out_file);
            OK_OR_RETURN();
            break;
    }
}
