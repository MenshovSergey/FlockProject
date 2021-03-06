#include<scene/scene.h>
#include<cassert>
#include<iostream>
#include<string>

using namespace std;
namespace scene
{
    void scene::add(boost::shared_ptr<object::object_vis>   new_obj)
    {
        object_list.push_back(new_obj);
		looks.insert(make_pair(new_obj, boost::make_shared <look>()));
        frame->add_object(looks[new_obj]); 
        ++list_size;
    }

    void scene::remove(size_t obj_id)
    {
        object_list.pop_back(); //TODO: remove object by id
        --list_size;
    }

    object::object_vis const & scene::access  (size_t obj_id)
    {
        assert((0 <= obj_id) && (obj_id < list_size));
        return *object_list[obj_id];
    }

    vector<boost::shared_ptr<object::object_vis>>const &  scene::content()
    {
        return object_list;
    }

    void scene::update()
    {
        for (int i = 0; i < list_size; ++i)
        {
            object_list[i]->update();
        }
    }

    void scene::render()
    {

        for (int i = 0; i < list_size; ++i)
        {
            look temp = object_list[i]->render();
            *looks[object_list[i]] = temp;
        }

    }

    void scene::init(scene_3d & new_master)
    {
        frame = &new_master;
		//frame = boost::make_shared<scene_3d>(new_master);
    }

    scene::scene()
        : object_list(0)
        , list_size(0)
        , frame (0)
    {
    }

    scene::~scene()
    {
    }

} //world
