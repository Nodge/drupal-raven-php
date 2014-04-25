<?php

/**
 * @file
 * Contains the administration pages for raven.
 *
 */

function raven_settings_form($form, &$form_state) {
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
    '#description' => t('Check for handling fatal errors.'),
    '#default_value' => variable_get('raven_fatal_error_handler', TRUE),
  );

  $form['raven_settings']['raven_error_handler'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable error handler'),
    '#description' => t('Check for handling errors through watchdog.'),
    '#default_value' => variable_get('raven_error_handler', TRUE),
  );

  $form['raven_settings']['raven_error_levels'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Error levels'),
    '#description' => t('Check error levels to handle.'),
    '#default_value' => variable_get('raven_error_levels', array()),
    '#options' => array(
      'e' . WATCHDOG_DEBUG => 'WATCHDOG_DEBUG',
      'e' . WATCHDOG_INFO => 'WATCHDOG_INFO',
      'e' . WATCHDOG_ALERT => 'WATCHDOG_ALERT',
      'e' . WATCHDOG_NOTICE => 'WATCHDOG_NOTICE',
      'e' . WATCHDOG_WARNING => 'WATCHDOG_WARNING',
      'e' . WATCHDOG_ERROR => 'WATCHDOG_ERROR',
      'e' . WATCHDOG_CRITICAL => 'WATCHDOG_CRITICAL',
      'e' . WATCHDOG_EMERGENCY => 'WATCHDOG_EMERGENCY',
    )
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

