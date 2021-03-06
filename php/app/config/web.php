<?php

$params = array_merge(
    require __DIR__ . '/params.php',
    require __DIR__ . '/params-local.php'
);
$db = array_merge(
    require __DIR__ . '/db.php',
    require __DIR__ . '/db-local.php'
);

$config = [
    'id' => 'mqttsub',
    'basePath' => dirname(__DIR__),
    'vendorPath'=>__DIR__.'/../../vendor',
    'components' => [
        'request' => [
            // !!! insert a secret key in the following (if it is empty) - this is required by cookie validation
            // 'enableCookieValidation' => false,
            'enableCsrfValidation' => false,
            'cookieValidationKey' => 'yiimqttsub',
            // 'parsers' => [
            //     'application/json' => 'yii\web\JsonParser',
            // ]
        ],
        'db' => $db,
        'log' => [
            'targets' => [
                    [
                    'class' => 'yii\log\FileTarget',
                    'levels' => ['trace', 'info', 'error', 'warning'],
                    'logVars' => ['*'],
                    // 'categories' => ['routine'],
                    // 'logFile' => '@runtime/logs/routine.log',
                ],
                [
                    'class' => 'yii\log\FileTarget',
                    'levels' => ['trace','info', 'error', 'warning'],
                    'logVars' => ['*'],
                    'categories' => ['routine'],
                    'logFile' => '@runtime/logs/routine.log',
                ],
            ],
        ],
     ], 
    // 'defaultRoute' => 'fapan', 
    // 'defaultController' => 'index' 
    'language' => 'zh-CN',
    'timeZone' => 'Asia/Shanghai',
    'sourceLanguage' => 'en-US',
    'params' => $params,
];

if (YII_ENV_DEV) {
    // configuration adjustments for 'dev' environment
    $config['bootstrap'][] = 'debug';
    $config['modules']['debug'] = [
        'class' => 'yii\debug\Module',
        // uncomment the following to add your IP if you are not connecting from localhost.
        //'allowedIPs' => ['127.0.0.1', '::1'],
    ];

    $config['bootstrap'][] = 'gii';
    $config['modules']['gii'] = [
        'class' => 'yii\gii\Module',
        // uncomment the following to add your IP if you are not connecting from localhost.
        //'allowedIPs' => ['127.0.0.1', '::1'],
    ];
}

return $config;
