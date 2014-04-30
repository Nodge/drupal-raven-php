<?php

/**
 * @file
 * Contains the administration pages for raven.
 *
 */

function raven_settings_form($form, &$form_state) {
  _raven_get_client(); // show message if library can not be loaded

  $form['raven_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Raven-php logging'),
    '#description' => t('Enable logging to send reports to Sentry server.'),
    '#default_value' => variable_get('raven_enabled', FALSE),
  );

  $form['raven_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Logging settings'),
    '#states' => array(
      'disabled' => array(
        ':input[name="raven_enabled"]' => array('unchecked' => TRUE),
      ),
    ),
  );

  $form['raven_settings']['raven_dsn'] = array(
    '#type' => 'textfield',
    '#title' => t('Sentry DSN'),
    '#description' => t('Sentry DSN credentials for current site.'),
    '#default_value' => variable_get('raven_dsn', ''),
  );

  $form['raven_settings']['raven_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout'),
    '#description' => t('Connection timeout in seconds.'),
    '#default_value' => variable_get('raven_timeout', 2),
  );

  $form['raven_settings']['raven_exception_handler'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable exception handler'),
    '#description' => t('Check for handling uncaught exceptions.'),
    '#default_value' => variable_get('raven_exception_handler', TRUE),
  );

  $form['raven_settings']['raven_fatal_error_handler'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable fatal error handler'),
    '#description' => t('Check for handling fatal php errors.'),
    '#default_value' => variable_get('raven_fatal_error_handler', TRUE),
  );

  $form['raven_settings']['raven_fatal_error_handler_memory'] = array(
    '#type' => 'textfield',
    '#title' => t('Reserved memory'),
    '#description' => t('Reserved memory for fatal error handler (KB).'),
    '#default_value' => variable_get('raven_fatal_error_handler_memory', 2.5*1024),
    '#size' => 10,
  );

  $form['raven_settings']['raven_error_handler'] = array(
    '#type' => 'fieldset',
    '#title' => t('Error handler'),
  );

  $form['raven_settings']['raven_error_handler']['raven_error_handler'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable error handler'),
    '#description' => t('Check for handling php errors.'),
    '#default_value' => variable_get('raven_error_handler', TRUE),
  );

  $form['raven_settings']['raven_error_handler']['raven_error_levels'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Error levels'),
    '#description' => t('Check error levels to handle.'),
    '#default_value' => variable_get('raven_error_levels', array()),
    '#options' => raven_get_error_levels(),
    '#states' => array(
      'disabled' => array(
        ':input[name="raven_error_handler"]' => array('unchecked' => TRUE),
      ),
    ),
  );

  $form['raven_settings']['raven_watchdog_handler'] = array(
    '#type' => 'fieldset',
    '#title' => t('Watchdog handler'),
  );

  $form['raven_settings']['raven_watchdog_handler']['raven_watchdog_handler'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable watchdog handler'),
    '#description' => t('Check for handling watchdog messages (except php errors).'),
    '#default_value' => variable_get('raven_watchdog_handler', FALSE),
  );

  $_watchdog_levels = raven_get_watchdog_levels();
  $watchdog_levels = array();
  foreach ($_watchdog_levels as $level => $label) {
    $watchdog_levels[$level + 1] = $label;
  }
  $form['raven_settings']['raven_watchdog_handler']['raven_watchdog_levels'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Message levels'),
    '#description' => t('Check message levels to handle.'),
    '#default_value' => variable_get('raven_watchdog_levels', array()),
    '#options' => $watchdog_levels,
    '#states' => array(
      'disabled' => array(
        ':input[name="raven_watchdog_handler"]' => array('unchecked' => TRUE),
      ),
    ),
  );

  $form['raven_settings']['raven_stack'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable stacktraces'),
    '#description' => t('Enable it to add stacktraces to reports.'),
    '#default_value' => variable_get('raven_stack', TRUE),
  );

  $form['raven_settings']['raven_trace'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reflection tracing in stacktraces'),
    '#description' => t('Check this to enable reflection tracing (function calling arguments) in stacktraces.'),
    '#default_value' => variable_get('raven_trace', FALSE),
  );

//	$form['#submit'] = array('raven_settings_form_submit');

  return system_settings_form($form);
}

/*function raven_settings_form_submit($form, &$form_state) {

}*/

