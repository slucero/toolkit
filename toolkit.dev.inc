<?php
/**
 * @file
 * Include file for dev utility functions.
 */

/**
 * A utility function for easily debugging function arguments.
 *
 * Outputs a function's name and its arguments.
 *
 * @see fd().
 */
function function_debug() {
  $trace = debug_backtrace();
  $output = array();

  if ($trace[1]['function'] == 'fd') {
    $output = array(
      $trace[2]['function'] => $trace[2]['args'],
    );
  }
  else {
    $output = array(
      $trace[1]['function'] => $trace[1]['args'],
    );
  }

  dpm($output);
}

/**
 * A utility function for programatically reverting designated modules.
 *
 * @param $modules
 *   An array of module names to be reverted.
 */
function toolkit_feature_revert($modules) {
  module_load_include('inc', 'features', 'features.export');
  features_include();

  foreach ($modules as $module) {
    if (($feature = feature_load($module, TRUE)) && module_exists($module)) {
      $components = array();
      // Forcefully revert all components of a feature.
      foreach (array_keys($feature->info['features']) as $component) {
        if (features_hook($component, 'features_revert')) {
          $components[] = $component;
        }
      }
    }
    foreach ($components as $component) {
      features_revert(array($module => array($component)));
    }
  }
}

/**
 * Return the reference count of a variable.
 * 
 * Returns 0 if a variable has no reference other than itself or doesn't
 * exist.
 *
 * @see http://www.php.net/manual/en/function.debug-zval-dump.php#109146
 */
function refcount(&$var) {
  ob_start();
  debug_zval_dump(array(&$var));
  return preg_replace("/^.+?refcount\((\d+)\).+$/ms", '$1', substr(ob_get_clean(), 24), 1) - 4;
}

/**
 * Return whether a and b reference the same memory
 *
 * @see http://www.php.net/manual/en/function.debug-zval-dump.php#109146
*/
function reference(&$a, &$b) {
    $d = refcount($b);
    $e = &$a;
    return refcount($b) != $d;
}
