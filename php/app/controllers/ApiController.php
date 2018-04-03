<?php

namespace app\controllers;
use Yii;
use yii\data\ArrayDataProvider;
// use yii\data\ActiveDataProvider;
// use app\models\Cpdborder;
// use yii\helpers\Url;
use yii\web\NotFoundHttpException;
use yii\web\ServerErrorHttpException;
// use yii\db\Query;
use app\models\Routine;
class ApiController extends \yii\web\Controller
{
    public function actionTest()
    {
    	// $routineObj = new Routine();
     //    $ret = $routineObj->test();
     //    return var_dump($ret);

    }
    public function actionIndex()
    {
    	$request = Yii::$app->request;
        $cmd = $request->post('cmd');
        $mid = $request->post('mid');
        $clientid = $request->post('clientid');
        // Yii::debug("cmd: " . $cmd, 'routine');
        // Yii::debug("mid: " . $mid, 'routine');
        // Yii::debug("clientid: " . $clientid, 'routine');
        // Yii::debug(sprintf("cmd: %s, mid: %s, clientid: %s", $cmd, $mid, $clientid), 'routine');
        $routineObj = new Routine();
        $ret = $routineObj->parseCmd($cmd, $mid, $clientid);
        return var_dump($ret);
    }

}