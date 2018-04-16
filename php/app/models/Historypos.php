<?php

namespace app\models;

use Yii;

/**
 * This is the model class for table "historypos".
 *
 * @property string $machine_id
 * @property string $activetime
 * @property double $lat
 * @property double $lon
 * @property int $radius
 * @property string $address
 *
 * @property Machine $machine
 */
class Historypos extends \yii\db\ActiveRecord
{
    /**
     * @inheritdoc
     */
    public static function tableName()
    {
        return 'historypos';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['machine_id', 'activetime'], 'required'],
            [['activetime'], 'safe'],
            [['lat', 'lon'], 'number'],
            [['radius'], 'integer'],
            [['machine_id'], 'string', 'max' => 10],
            [['address'], 'string', 'max' => 45],
            [['machine_id', 'activetime'], 'unique', 'targetAttribute' => ['machine_id', 'activetime']],
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
            'lat' => 'Lat',
            'lon' => 'Lon',
            'radius' => 'Radius',
            'address' => 'Address',
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
