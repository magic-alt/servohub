This is a fork of the CanFestival-3 project http://dev.automforge.net/CanFestival-3

Latest work done:

- Fix some big endian issues and remove compiler warnings by adding explicit casts. Thanks to Casey Klimasuskas for sharing.

- The Canopen dictionary editor Objdictedit.py now allows to define the size of each string or domain, thanks to Mattes Standfuß for his work 

- The stack can now be compiled as a .so shared lib, thanks to Mattes Standfuß for this also

- New example added : examples/linux/dcf

- I needed the stack to be more dynamic, i wanted to be able to dynamically build the OD and the CO_Data struct without any global declaration, so i have made few changes. (this is not a dirty hack it is even cleaner i think)

- solving array of string or domain issue (search for "Array of strings issue" in the mailing list)

- solving bugs on sdo block transfer and dcf management

- stm32F0/F1/F4 basic support

Any feedback, comment, is welcome.

You can contact me at : 
fbeaulier < a t > orange < d o t > fr

## ServoHub reproducible object-dictionary generation

ServoHub now keeps the CanFestival runtime in this directory but uses the
maintained Python 3 `objdictgen`/`odg` tool for local object-dictionary
generation. The repository-specific wrapper, pinned dependency, CiA 402 typed
contract, JSONC migration command, and CMake targets live under:

`tools/canopen_codegen/`

Do not edit `SlaveOD.c` or `SlaveOD.h` manually. Edit the canonical OD source
(currently `SlaveOD.eds`; planned migration target `SlaveOD.jsonc`) and
regenerate the artifacts. See `tools/canopen_codegen/README.md`.
