my_shell=$0
rootcore_setup="${BASH_SOURCE:-$0}"
rootcore_dir=`dirname $rootcore_setup | xargs dirname`
eval `$rootcore_dir/internal/env_setup --shell $my_shell $rootcore_setup`
