<?php

use yii\helpers\Html;
use yii\grid\GridView;

/* @var $this yii\web\View */
/* @var $searchModel app\models\MachineSearch */
/* @var $dataProvider yii\data\ActiveDataProvider */

$this->title = 'Machines';
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="machine-index">

    <h1><?= Html::encode($this->title) ?></h1>
    <?php // echo $this->render('_search', ['model' => $searchModel]); ?>

    <?= GridView::widget([
        'dataProvider' => $dataProvider,
        'filterModel' => $searchModel,
        'columns' => [
            // ['class' => 'yii\grid\SerialColumn'],
            'newstat.activetime',
            'mtype',
            'id',
            // 'newstat.online',
            [
                'attribute' => 'newstat.online',
                'format' => 'html',
                'content' => function ($model,$key, $index, $column) {
                    return $model['newstat']['online'];
                
                },
                'contentOptions' => function ($model,$key, $index, $column) {
                    if ($model['newstat']['online'] == 'N') {
                        return ['style'=>"color:red"];
                    } else {
                        return ['style'=>"color:green"];
                    }

                }
            ],
            // 'newpos.address',
            [
                'attribute' => 'address',
                'content' => function ($model,$key, $index, $column) {
                    $newpos = $model->newpos;
                    if (empty($newpos)) 
                        return "";
                    $url = sprintf("https://ditu.amap.com/regeo?lng=%s&lat=%s&src=uriapi", $newpos['lon'], $newpos['lat']);
                    return Html::a($newpos['address'], $url, ["target" => "_blank"]);
                
                }
            ],


        ],
    ]); ?>
</div>
