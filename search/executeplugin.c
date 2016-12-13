//make a new menu for plugin options
if !variable_global_exists("pluginOptions") {
    global.pluginOptions = object_add();
    object_set_parent(global.pluginOptions,OptionsController);  
    object_set_depth(global.pluginOptions,-130000); 
    object_event_add(global.pluginOptions,ev_create,0,'   
        menu_create(40, 140, 300, 200, 30);
    
        if room != Options {
            menu_setdimmed();
        }
    
        menu_addback("Back", "
            instance_destroy();
            if(room == Options)
                instance_create(0,0,MainMenuController);
            else
                instance_create(0,0,InGameMenuController);
        ");
    ');   
    object_event_add(InGameMenuController,ev_create,0,'
        menu_addlink("Plugin Options", "
            instance_destroy();
            instance_create(0,0,global.pluginOptions);
        ");
    ');
} 

//script taken from ingame
global.loadpluginscript = '
    // self-explanatory
    // borrowed file-search code from Port
    var file, pattern, prefix, list, fp, i;
    // Prefix since results from file_find_* don't include path
    prefix = working_directory + "Plugins/Scripts";
    pattern = prefix + "*.gml";

    list = ds_list_create();

    // Find files and put in list
    for (file = file_find_first(pattern, 0); file != ""; file = file_find_next())
    {
        ds_list_add(list, file);
    }

    // Execute plugins
    for (i = 0; i < ds_list_size(list); i += 1)
    {
        file = ds_list_find_value(list, i);
        // Debugging facility, so we know *which* plugin caused compile/execute error
        fp = file_text_open_write(working_directory + "\last_plugin.log");
        file_text_write_string(fp, prefix + file);
        file_text_close(fp);
        // Execute    
        execute_file(prefix + file);
    }

    // Clear up
    file_delete(working_directory + "\last_plugin.log");
    ds_list_destroy(list);
';
 
if(!directory_exists(working_directory + "/Plugins/Scripts"))
directory_create(working_directory + "/Plugins/Scripts");
object_event_add(global.pluginOptions,ev_create,0,'
//extremely shitty workaround
_execute = "Execute Plugin"
    menu_addlink(_execute, "
    execute_string(global.loadpluginscript);
    ");
');
