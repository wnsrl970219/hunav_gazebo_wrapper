# hunav_gazebo_wrapper

A ROS2 wrapper to use the [HuNavSim](https://github.com/robotics-upo/hunav_sim) with the Gazebo Simulator (tested with ROS Foxy and Gazebo 11). 

## Wrapper functioning

The wrapper is based on two components:

* The *hunav_gazebo_world_generator* node **(ongoing work)**. It is in charge of reading the simulation configuration parameters (human agents parameters) from the *hunav_loader* node, and the base Gazebo world file. With these parameters, the node modifies the base world file and includes the indicated human agents and the Gazebo plugin to control them (HuNavPlugin).

* The *HuNavPlugin* is a Gazebo plugin in charge of interacting with the HuNavSim to control the human movements. This interaction is performed through ROS2 services. 

![](https://github.com/robotics-upo/hunav_gazebo_wrapper/blob/master/media/images/hunav_gazebo_wrapper.png)

## Generator parameters

The *hunav_gazebo_world_generator* node has these parameters:

*  ```gazebo_world_file```. Name of the base Gazebo world file. This world should contain the static models (obstacles, rooms, furniture, etc). The human agents will be added automatically to this world. The world files must be placed inside the directory *worlds*.  
 

### Plugin params

The plugin parameters are read as ROS2 parameters also by the *hunav_gazebo_world_generator* node, which is in charge of adding the plugin to the Gazebo world file

*  ```update_rate```. Update rate (Hz) of the plugin proccess.
*  ```robot_name```. Name of the Gazebo model corresponding to the robot that will be spawned.
*  ```use_gazebo_obs```. Factor employed to coordinate the animation with the walking velocity.
* ```global_frame_to_publish```. Coordinate frame in which the pedestrian positions are provided.
* ```ignore_models```. List of the Gazebo models than must be ignored by the pedestrians like the ground plane.

An example snippet of the HuNavPlugin which is automatically inserted in the world file:

```html
<plugin name="hunav_plugin" filename="libHuNavPlugin.so">
    <update_rate>100.0</update_rate>
    <robot_name>robot</robot_name>
    <use_gazebo_obs>True</use_gazebo_obs>
    <global_frame_to_publish>map</global_frame_to_publish>
    <ignore_models>
    	<model>cafe</model>
        <model>ground_plane</model>
    </ignore_models>
</plugin>
```

## Dependencies

* The HuNavSim: https://github.com/robotics-upo/hunav_sim
* The ROS2 package *gazebo_ros_pkgs* is also required. 

## Compilation

* This is a ROS2 package so it must be placed inside a ROS2 workspace and compiled through the regular colcon tool. 

## Example

An example Gazebo world can be launched through:
```sh
ros2 launch _hunav_gazebo_wrapper cafe.launch.py
```
