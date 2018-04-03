<?php

namespace app\models;

use Yii;

/**
 * This is the model class for table "newstat".
 *
 * @property string $machine_id
 * @property string $activetime
 * @property string $online
 *
 * @property Machine $machine
 */
class Newstat extends \yii\db\ActiveRecord
{
    /**
     * @inheritdoc
     */
    public static function tableName()
    {
        return 'newstat';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['machine_id'], 'required'],
            [['activetime'], 'safe'],
            [['online'], 'string'],
            [['machine_id'], 'string', 'max' => 10],
            [['machine_id'], 'unique'],
            [['machine_id'], 'exist', 'skipOnError' => true, 'targetClass' => Machine::className(), 'targetAttribute' => ['machine_id' => 'id']],
        ];
    }

    /**
     * @inheritdoc
     */
    public function attributeLabels()
    {
        return [
            'machine_id' => 'Machine ID',
            'activetime' => 'Activetime',
            'online' => 'Online',
        ];
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getMachine()
    {
        return $this->hasOne(Machine::className(), ['id' => 'machine_id']);
    }
}
