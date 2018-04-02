<?php

use yii\helpers\Html;
use yii\widgets\ActiveForm;

/* @var $this yii\web\View */
/* @var $model app\models\Newstat */
/* @var $form yii\widgets\ActiveForm */
?>

<div class="newstat-form">

    <?php $form = ActiveForm::begin(); ?>

    <?= $form->field($model, 'machine_id')->textInput(['maxlength' => true]) ?>

    <?= $form->field($model, 'activetime')->textInput() ?>

    <?= $form->field($model, 'online')->dropDownList([ 'Y' => 'Y', 'N' => 'N', ], ['prompt' => '']) ?>

    <div class="form-group">
        <?= Html::submitButton('Save', ['class' => 'btn btn-success']) ?>
    </div>

    <?php ActiveForm::end(); ?>

</div>
