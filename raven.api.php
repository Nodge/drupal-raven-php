<?php

/**
 * Provide user information for logging.
 *
 * @param array $user
 */
function hook_raven_user_alter(&$user) {
  global $user;
  if (user_is_logged_in()) {
    $variables['id'] = $user->uid;
    $variables['name'] = $user->name;
    $variables['email'] = $user->mail;
    $variables['roles'] = implode(', ', $user->roles);
  }
}

/**
 * Provide tags for logging.
 *
 * @param array $tags
 */
function hook_raven_tags_alter(&$tags) {

}

/**
 * Provide extra information for logging.
 *
 * @param array $extra
 */
function hook_raven_extra_alter(&$extra) {

}

/**
 * Filter Raven-php errors.
 *
 * @param array $filter
 */
function hook_raven_error_filter_alter(&$filter) {
  static $known_errors;
  $error = & $filter['log_entry'];

  if (!isset($known_errors)) {
    $known_errors = array(
      'php' => array(
        '%type: !message in %function (line %line of %file).' => array(
          array(
            '%file' => DRUPAL_ROOT . '/sites/all/modules/views/plugins/views_plugin_cache.inc',
            '%line' => 206,
            '!message' => 'Array to string conversion',
          ),
        ),
      ),
    );
  }

  // Filter known errors to prevent spamming the Sentry server.
  if (isset($known_errors[$error['type']][$error['message']])) {
    foreach ($known_errors[$error['type']][$error['message']] as $variables) {
      $check = TRUE;
      foreach ($variables as $key => $value) {
        if (!isset($error['variables'][$key]) || $error['variables'][$key] != $value) {
          $check = FALSE;
          break;
        }
      }

      if ($check) {
        $filter['process'] = FALSE;
        break;
      }
    }
  }
}