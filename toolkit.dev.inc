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
