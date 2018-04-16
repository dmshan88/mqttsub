<?php

namespace app\models;

use Yii;

/**
 * This is the model class for table "newpos".
 *
 * @property string $machine_id
 * @property string $lastpostdate
 * @property string $mcc
 * @property string $mnc
 * @property string $lac
 * @property string $ci
 * @property double $lat
 * @property double $lon
 * @property string $address
 *
 * @property Machine $machine
 */
class Newpos extends \yii\db\ActiveRecord
{
    /**
     * @inheritdoc
     */
    public static function tableName()
    {
        return 'newpos';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['machine_id'], 'required'],
            [['lastpostdate'], 'safe'],
            [['mcc', 'mnc', 'lac', 'ci'], 'integer'],
            [['lat', 'lon'], 'number'],
            [['machine_id'], 'string', 'max' => 10],
            [['address'], 'string', 'max' => 45],
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
            'lastpostdate' => 'Lastpostdate',
            'mcc' => 'Mcc',
            'mnc' => 'Mnc',
            'lac' => 'Lac',
            'ci' => 'Ci',
            'lat' => 'Lat',
            'lon' => 'Lon',
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
