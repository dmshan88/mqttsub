<?php

use yii\helpers\Html;
use yii\grid\GridView;

/* @var $this yii\web\View */
/* @var $searchModel app\models\NewstatSearch */
/* @var $dataProvider yii\data\ActiveDataProvider */

$this->title = 'Newstats';
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="newstat-index">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= GridView::widget([
        'dataProvider' => $dataProvider,
        'filterModel' => $searchModel,
        'columns' => [
            ['class' => 'yii\grid\SerialColumn'],

            'activetime',
            [
                'attribute' => 'type',
                'class' => 'yii\grid\DataColumn', // can be omitted, as it is the default
                'content' => function ($model,$key, $index, $column) {
                    return $model->machine->mtype;
                
                },
            ],
            'machine_id',
            [
                'attribute' => 'address',
                'format' => 'html',
                'content' => function ($model,$key, $index, $column) {
                    $newpos = $model->machine->newpos;
                    if (empty($newpos)) {
                        return "";
                    } else {
                        // return $newpos->address;

                        $url = sprintf("https://ditu.amap.com/regeo?lng=%s&lat=%s&src=uriapi", $newpos->lon, $newpos->lat);
                        return Html::a($newpos->address, $url, ["target" => "_blank"]);
                    }
                    // var_dump($model->machine->newpos);
                    // return $model->machine->newpos->tableName();
                
                },
            ],
            [                                                  // the owner name of the model
                'attribute' => 'online',
                'format' => 'html',
                'content' => function ($model,$key, $index, $column) {
                    return $model->online;
                
                },
                'contentOptions' => function ($model,$key, $index, $column) {
                    if ($model->online == 'N') {
                        return ['style'=>"color:red"];
                    } else {
                        return ['style'=>"color:green"];
                    }

                }
            ],

            // ['class' => 'yii\grid\ActionColumn'],
        ],
    ]); ?>
</div>
